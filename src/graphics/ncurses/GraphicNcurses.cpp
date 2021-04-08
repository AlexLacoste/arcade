/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#include <iostream>
#include <memory>
#include <ncurses.h>
#include <string>
#include <thread>
#include "Ncurses.hpp"

extern "C" std::unique_ptr<ncurses::GraphicNcurses> entry_point()
{
    return std::make_unique<ncurses::GraphicNcurses>();
}

ncurses::GraphicNcurses::GraphicNcurses()
{
}

ncurses::GraphicNcurses::~GraphicNcurses()
{
    if (this->windowIsOpen)
        endwin();
}

int ncurses::GraphicNcurses::availableOptions() const
{
    return NO_OPTIONS;
}

bool ncurses::GraphicNcurses::isOpen()
{
    return this->windowIsOpen;
}

void ncurses::GraphicNcurses::init(const std::string &title, const unsigned int limit)
{
    (void)title;
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    // this->hasColors = has_colors();
    this->windowIsOpen = true;
    this->eventFrame = false;
    this->frameLimit = limit;
    // if (this->hasColors)
    //     start_color();
}

void ncurses::GraphicNcurses::display()
{
    this->eventFrame = false;
    refresh();
    double toWait = ((1.0f / this->frameLimit) * 1000) - (getFrameDuration() * 1000);
    if (toWait > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(toWait)));
    }
    this->lastFrameTime = getFrameDuration();
    restartClock();
}

void ncurses::GraphicNcurses::stop()
{
    echo();
    endwin();
    this->windowIsOpen = false;
}

void ncurses::GraphicNcurses::clearWindow()
{
    erase();
}

void ncurses::GraphicNcurses::restartClock()
{
    this->time = std::chrono::high_resolution_clock::now();
}

double ncurses::GraphicNcurses::getDeltaTime()
{
    return this->lastFrameTime;
}

double ncurses::GraphicNcurses::getFrameDuration() const
{
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
        std::chrono::high_resolution_clock::now() - this->time)
        .count();
}

arcade::data::Vector2u ncurses::GraphicNcurses::getWindowSize()
{
    return arcade::data::Vector2u{
        static_cast<unsigned int>(COLS), static_cast<unsigned int>(LINES)};
}

std::vector<arcade::data::Event> ncurses::GraphicNcurses::getEvents()
{
    if (this->eventFrame)
        return this->events;
    int key = getch();
    this->events.clear();
    this->eventFrame = true;
    this->events.emplace_back(
        arcade::data::EventType::KEY_PRESSED, static_cast<arcade::data::KeyCode>(key));
    return this->events;
}

void ncurses::GraphicNcurses::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    arcade::data::Vector2f pos = text->getPosition();
    mvprintw(pos.y, pos.x, text->getText().c_str());
}

void ncurses::GraphicNcurses::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    arcade::data::Vector2f pos = sprite->getPosition() + sprite->getOrigin();
    std::vector<std::string> spriteNcurses =
        reinterpret_cast<std::unique_ptr<SpriteNcurses> &>(sprite)->getSpriteNcurses();
    for (std::size_t i = 0; i < spriteNcurses.size(); i++) {
        mvprintw(pos.y + i, pos.x, spriteNcurses.at(i).c_str());
    }
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText(
    const std::string &text)
{
    return std::make_unique<TextNcurses>(text);
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText()
{
    return std::make_unique<TextNcurses>();
}

std::unique_ptr<arcade::displayer::ISprite> ncurses::GraphicNcurses::createSprite()
{
    return std::make_unique<SpriteNcurses>();
}

std::unique_ptr<arcade::displayer::ISprite> ncurses::GraphicNcurses::createSprite(
    const std::string &spritePath, const std::vector<std::string> &asciiSprite,
    arcade::data::Vector2f scale)
{
    return std::make_unique<SpriteNcurses>(spritePath, asciiSprite, scale);
}

double ncurses::GraphicNcurses::scaleMoveX(double time)
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double ncurses::GraphicNcurses::scaleMoveY(double time)
{
    if (!time) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}