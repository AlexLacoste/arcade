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
    return arcade::data::FloatRect{0, 0, static_cast<float>(this->str.length()), 1};
}

arcade::data::FloatRect ncurses::TextNcurses::getGlobalBounds()
{
    return arcade::data::FloatRect{this->pos.y - this->origin.y, this->pos.x - this->origin.x, static_cast<float>(this->str.length()), 1};
}

void ncurses::TextNcurses::setOrigin(arcade::data::Vector2f origin) // TODO: make origin
{
    this->origin = origin;
}

arcade::data::Vector2f ncurses::TextNcurses::getOrigin()
{
    return this->origin;
}