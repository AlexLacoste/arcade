/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** SpriteNcurses
*/

#include "Ncurses.hpp"

ncurses::SpriteNcurses::SpriteNcurses()
{
}

ncurses::SpriteNcurses::SpriteNcurses(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
}

ncurses::SpriteNcurses::~SpriteNcurses()
{
}

void ncurses::SpriteNcurses::setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
}

void ncurses::SpriteNcurses::setPosition(arcade::data::Vector2f pos)
{
}

arcade::data::Vector2f ncurses::SpriteNcurses::getPosition() const
{
    return arcade::data::Vector2f{};
}

void ncurses::SpriteNcurses::move(arcade::data::Vector2f pos)
{
}

void ncurses::SpriteNcurses::move(float x, float y)
{
}

void ncurses::SpriteNcurses::setOrigin(arcade::data::Vector2f origin)
{
}

arcade::data::Vector2f ncurses::SpriteNcurses::getOrigin()
{
    return arcade::data::Vector2f{};
}

arcade::data::FloatRect ncurses::SpriteNcurses::getLocalBounds()
{
    return arcade::data::FloatRect{};
}

void ncurses::SpriteNcurses::setScale(arcade::data::Vector2f scale)
{
}

arcade::data::Vector2f ncurses::SpriteNcurses::getScale()
{
    return arcade::data::Vector2f{};
}

float ncurses::SpriteNcurses::getRotation()
{
    return 0.0;
}

void ncurses::SpriteNcurses::setRotation(float angle)
{
}

void ncurses::SpriteNcurses::rotate(float angle)
{
}

void ncurses::SpriteNcurses::setTextureRect(const arcade::data::IntRect &rect)
{
}

arcade::data::IntRect ncurses::SpriteNcurses::getTextureRect() const
{
    return arcade::data::IntRect{};
}

void ncurses::SpriteNcurses::setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
}