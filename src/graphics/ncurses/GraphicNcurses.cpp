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

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText(const std::string &text)
{
    return std::make_unique<TextNcurses>(text);
}

std::unique_ptr<arcade::displayer::IText> ncurses::GraphicNcurses::createText()
{
    return std::make_unique<TextNcurses>();
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