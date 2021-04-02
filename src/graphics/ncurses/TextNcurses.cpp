/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** TextSfml
*/

#include "Ncurses.hpp"

ncurses::TextNcurses::TextNcurses()
{
}

ncurses::TextNcurses::TextNcurses(const std::string &text)
{
    this->str = text;
}

ncurses::TextNcurses::~TextNcurses()
{
}

void ncurses::TextNcurses::setText(const std::string &text)
{
    this->str = text;
}

std::string ncurses::TextNcurses::getText() const
{
    return this->str;
}

void ncurses::TextNcurses::setPosition(arcade::data::Vector2f pos)
{
    this->pos = pos;
}

arcade::data::Vector2f ncurses::TextNcurses::getPosition() const
{
    return this->pos;
}

void ncurses::TextNcurses::setFont(const std::string &font)
{
    (void)font;
}

void ncurses::TextNcurses::setColor(arcade::data::Color color)
{
    this->color = color;
}

arcade::data::Color ncurses::TextNcurses::getColor() const
{
    return this->color;
}

void ncurses::TextNcurses::setCharacterSize(unsigned int size)
{
    (void)size;
}

arcade::data::FloatRect ncurses::TextNcurses::getLocalBounds()
{
    return arcade::data::FloatRect{this->pos.x, this->pos.y, static_cast<float>(this->str.length()), 1};
}

void ncurses::TextNcurses::setOrigin(arcade::data::Vector2f origin)
{
    this->pos = {origin.x, origin.y};
}

arcade::data::Vector2f ncurses::TextNcurses::getOrigin()
{
    return this->pos;
}