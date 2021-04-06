/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#include <memory>
#include <ncurses.h>
#include <iostream>
#include <string>
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
    std::cout << "Is close lib" << std::endl;
    if (this->windowIsOpen)
        endwin();
}

bool ncurses::GraphicNcurses::isOpen()
{
    return this->windowIsOpen;
}

void ncurses::GraphicNcurses::init(const std::string &title, const unsigned int limit)
{
    (void)title;
    (void)limit;
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
    this->hasColors = has_colors();
    this->windowIsOpen = true;
    // if (this->hasColors)
    //     start_color();
}

void ncurses::GraphicNcurses::display()
{
    this->eventFrame = false;
    refresh();
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
{}

double ncurses::GraphicNcurses::getDeltaTime()
{
    return 10; // TODO : deltaTime ncurses
}

arcade::data::Vector2u ncurses::GraphicNcurses::getWindowSize()
{
    return arcade::data::Vector2u{static_cast<unsigned int>(COLS) , static_cast<unsigned int>(LINES)};
}

std::vector<arcade::data::Event> ncurses::GraphicNcurses::getEvents()
{
    if (this->eventFrame)
        return this->events;
    int key = getch();
    this->events.clear();
    this->eventFrame = true;
    this->events.emplace_back(arcade::data::EventType::KEY_PRESSED, static_cast<arcade::data::KeyCode>(key));
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
    std::vector<std::string> spriteNcurses = reinterpret_cast<std::unique_ptr<SpriteNcurses> &>(sprite)->getSpriteNcurses();
    for (int i = 0; i < spriteNcurses.size(); i++) {
        mvprintw(pos.y + i, pos.x, spriteNcurses.at(i).c_str());
    }
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText(const std::string &text)
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

std::unique_ptr<arcade::displayer::ISprite> ncurses::GraphicNcurses::createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
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