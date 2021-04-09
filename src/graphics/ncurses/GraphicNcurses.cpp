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
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(8, COLOR_CYAN, COLOR_BLACK);
    }
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    this->windowIsOpen = true;
    this->eventFrame = false;
    this->frameLimit = limit;
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
    if (has_colors()) {
        attron(COLOR_PAIR(goodColor(text->getColor())));
    }
    mvprintw(pos.y, pos.x, text->getText().c_str());
}

void ncurses::GraphicNcurses::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    arcade::data::Vector2f pos = sprite->getPosition() + sprite->getOrigin();
    std::vector<std::string> spriteNcurses =
        reinterpret_cast<std::unique_ptr<SpriteNcurses> &>(sprite)->getSpriteNcurses();
    std::vector<std::vector<arcade::data::Color>> colorNcurses =
        reinterpret_cast<std::unique_ptr<SpriteNcurses> &>(sprite)->getColor();
    for (std::size_t i = 0; i < spriteNcurses.size(); i++) {
        for (std::size_t j = 0; j < spriteNcurses.at(i).length(); j++) {
            if (spriteNcurses.at(i).at(j) != ' ') {
                if (has_colors()) {
                    attron(COLOR_PAIR(goodColor(colorNcurses.at(i).at(j))));
                }
                mvaddch(pos.y + i, pos.x + j, spriteNcurses.at(i).at(j));
            }
        }
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

int ncurses::GraphicNcurses::goodColor(const arcade::data::Color &color)
{
    if (color == arcade::data::Color(0, 0, 0, 255))
        return (1);
    if (color == arcade::data::Color(255, 0, 0, 255))
        return (3);
    if (color == arcade::data::Color(0, 255, 0, 255))
        return (4);
    if (color == arcade::data::Color(0, 0, 255, 255))
        return (5);
    if (color == arcade::data::Color(255, 255, 0, 255))
        return (6);
    if (color == arcade::data::Color(255, 0, 255, 255))
        return (7);
    if (color == arcade::data::Color(0, 255, 255, 255))
        return (8);
    if (color == arcade::data::Color(255, 255, 255, 0))
        return (1);
    return (2);
}