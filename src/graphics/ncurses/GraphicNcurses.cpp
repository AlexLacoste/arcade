/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#include <memory>
#include <ncurses.h>
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

bool ncurses::GraphicNcurses::isOpen() const
{
    return this->windowIsOpen;
}

void ncurses::GraphicNcurses::init(const std::string &title, const unsigned int limit)
{
    (void)title;
    (void)limit;
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    this->windowIsOpen = true;
}

void ncurses::GraphicNcurses::display()
{
    refresh();
}

void ncurses::GraphicNcurses::stop()
{
    endwin();
    this->windowIsOpen = false;
}

void ncurses::GraphicNcurses::clearWindow()
{
    clear();
}

void ncurses::GraphicNcurses::restartClock()
{}

double ncurses::GraphicNcurses::getDeltaTime()
{
    return 10; // TODO : deltaTime ncurses
}

arcade::data::Vector2u ncurses::GraphicNcurses::getWindowSize()
{
    return arcade::data::Vector2u{static_cast<unsigned int>(LINES) , static_cast<unsigned int>(COLS)};
}

std::vector<arcade::data::Event> ncurses::GraphicNcurses::getEvents()
{
    return std::vector<arcade::data::Event>{};
}

void ncurses::GraphicNcurses::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    arcade::data::Vector2f pos = text->getPosition();
    mvprintw(pos.y, pos.x, text->getText().c_str());
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText(const std::string &text)
{
    return std::make_unique<TextNcurses>(text);
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText()
{
    return std::make_unique<TextNcurses>();
}