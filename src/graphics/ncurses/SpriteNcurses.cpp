/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** SpriteNcurses
*/

#include "Ncurses.hpp"

ncurses::SpriteNcurses::SpriteNcurses() : rotation(0)
{
}

ncurses::SpriteNcurses::SpriteNcurses(const std::string &spritePath,
    const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
    (void)spritePath;
    (void)scale;
    this->sprite = asciiSprite;
}

ncurses::SpriteNcurses::~SpriteNcurses()
{
}

void ncurses::SpriteNcurses::setSprite(
    const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)spritePath;
    this->sprite = asciiSprite;
}

void ncurses::SpriteNcurses::setPosition(arcade::data::Vector2f pos)
{
    this->pos = pos;
}

arcade::data::Vector2f ncurses::SpriteNcurses::getPosition() const
{
    return this->pos;
}

void ncurses::SpriteNcurses::move(arcade::data::Vector2f pos)
{
    this->pos =
        arcade::data::Vector2f{this->getPosition().x + pos.x, this->getPosition().y + pos.y};
}

void ncurses::SpriteNcurses::move(float x, float y)
{
    this->pos = arcade::data::Vector2f{this->getPosition().x + x, this->getPosition().y + y};
}

void ncurses::SpriteNcurses::setOrigin(arcade::data::Vector2f origin)
{
    this->origin = origin;
}

arcade::data::Vector2f ncurses::SpriteNcurses::getOrigin()
{
    return this->origin;
}

arcade::data::FloatRect ncurses::SpriteNcurses::getLocalBounds()
{
    if (this->sprite.size() == 0) {
        return arcade::data::FloatRect{0, 0, 0, static_cast<float>(this->sprite.size())};
    }
    return arcade::data::FloatRect{0, 0, static_cast<float>(this->sprite.at(0).length()),
        static_cast<float>(this->sprite.size())};
}

arcade::data::FloatRect ncurses::SpriteNcurses::getGlobalBounds()
{
    return arcade::data::FloatRect{this->pos.y - this->origin.y, this->pos.x - this->origin.x,
        static_cast<float>(this->textureRect.width), static_cast<float>(this->textureRect.height)};
}

void ncurses::SpriteNcurses::setScale(arcade::data::Vector2f scale)
{
    (void)scale;
}

arcade::data::Vector2f ncurses::SpriteNcurses::getScale()
{
    return arcade::data::Vector2f{1, 1};
}

float ncurses::SpriteNcurses::getRotation()
{
    return this->rotation;
}

void ncurses::SpriteNcurses::setRotation(float angle)
{
    this->rotation = angle;
}

void ncurses::SpriteNcurses::rotate(float angle)
{
    this->rotation += angle;
}

void ncurses::SpriteNcurses::setTextureRect(const arcade::data::IntRect &rect)
{
    this->textureRect = rect;
}

arcade::data::IntRect ncurses::SpriteNcurses::getTextureRect() const
{
    return this->textureRect;
}

void ncurses::SpriteNcurses::setColor(
    arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
    (void)color;
    this->asciiColors = asciiColors;
}

std::vector<std::string> ncurses::SpriteNcurses::getSpriteNcurses()
{
    return this->sprite;
}

std::vector<std::vector<arcade::data::Color>> ncurses::SpriteNcurses::getColor()
{
    return this->asciiColors;
}