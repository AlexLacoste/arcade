/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** TextSfml
*/

#include "Sfml.hpp"

sfml::TextSfml::TextSfml()
{
}

sfml::TextSfml::TextSfml(const std::string &text)
{
    this->text.setString(text);
}

sfml::TextSfml::~TextSfml()
{
}

void sfml::TextSfml::setText(const std::string &text)
{
    this->text.setString(text);
}

std::string sfml::TextSfml::getText() const
{
    return this->text.getString();
}

void sfml::TextSfml::setPosition(arcade::data::Vector2f pos)
{
    this->text.setPosition(pos.x, pos.y);
}

arcade::data::Vector2f sfml::TextSfml::getPosition() const
{
    sf::Vector2f sfPos = this->text.getPosition();
    return arcade::data::Vector2f{sfPos.x, sfPos.y};
}

void sfml::TextSfml::setFont(const std::string &font)
{
    this->font.loadFromFile(font);
}

void sfml::TextSfml::setColor(arcade::data::Color color)
{
    sf::Color sfColor{color.r, color.g, color.b, color.a};
    this->text.setFillColor(sfColor);
}

arcade::data::Color sfml::TextSfml::getColor() const
{
    sf::Color sfcolor = this->text.getFillColor();
    return arcade::data::Color{sfcolor.r, sfcolor.g, sfcolor.b, sfcolor.a};
}

void sfml::TextSfml::setCharacterSize(unsigned int size)
{
    (void)size;
}

arcade::data::FloatRect sfml::TextSfml::getLocalBounds()
{
    sf::FloatRect sfRect = this->text.getGlobalBounds();
    return arcade::data::FloatRect{sfRect.left, sfRect.top, sfRect.width, sfRect.height};
}

void sfml::TextSfml::setOrigin(arcade::data::Vector2f origin)
{
    sf::Vector2f sfOrigin{origin.x, origin.y};
    this->text.setOrigin(sfOrigin);
}

arcade::data::Vector2f sfml::TextSfml::getOrigin()
{
    sf::Vector2f sfOrigin = this->text.getOrigin();
    return arcade::data::Vector2f{sfOrigin.x, sfOrigin.y};
}

sf::Text sfml::TextSfml::getSfText() const
{
    return this->text;
}