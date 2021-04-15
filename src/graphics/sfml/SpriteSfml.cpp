/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** SpriteSfml
*/

#include "Sfml.hpp"
#include "../../shared/Errors.hpp"

sfml::SpriteSfml::SpriteSfml()
{
}

sfml::SpriteSfml::SpriteSfml(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale)
{
    this->setSprite(spritePath, asciiSprite);
    this->setScale(scale);
}

sfml::SpriteSfml::~SpriteSfml()
{
}

void sfml::SpriteSfml::setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)asciiSprite;
    if (!this->texture.loadFromFile(spritePath)) {
        throw arcade::errors::Error("SFML load sprite");
    }
    this->sprite.setTexture(this->texture);
}

void sfml::SpriteSfml::setPosition(arcade::data::Vector2f pos)
{
    this->sprite.setPosition(pos.x, pos.y);
}

arcade::data::Vector2f sfml::SpriteSfml::getPosition() const
{
    return arcade::data::Vector2f{this->sprite.getPosition().x, this->sprite.getPosition().y};
}

void sfml::SpriteSfml::move(arcade::data::Vector2f pos)
{
    this->sprite.move(pos.x, pos.y);
}

void sfml::SpriteSfml::move(float x, float y)
{
    this->sprite.move(x, y);
}

void sfml::SpriteSfml::setOrigin(arcade::data::Vector2f origin)
{
    this->sprite.setOrigin(origin.x, origin.y);
}

arcade::data::Vector2f sfml::SpriteSfml::getOrigin() const
{
    return arcade::data::Vector2f{this->sprite.getOrigin().x, this->sprite.getOrigin().y};
}

arcade::data::FloatRect sfml::SpriteSfml::getLocalBounds() const
{
    sf::FloatRect sfRect = this->sprite.getLocalBounds();
    return arcade::data::FloatRect{sfRect.top, sfRect.left, sfRect.width, sfRect.height};
}

arcade::data::FloatRect sfml::SpriteSfml::getGlobalBounds() const
{
    sf::FloatRect sfRect = this->sprite.getGlobalBounds();
    return arcade::data::FloatRect{sfRect.top, sfRect.left, sfRect.width, sfRect.height};
}

void sfml::SpriteSfml::setScale(arcade::data::Vector2f scale)
{
    this->sprite.setScale(scale.x, scale.y);
}

arcade::data::Vector2f sfml::SpriteSfml::getScale() const
{
    return arcade::data::Vector2f{this->sprite.getScale().x, this->sprite.getScale().y};
}

float sfml::SpriteSfml::getRotation() const
{
    return this->sprite.getRotation();
}

void sfml::SpriteSfml::setRotation(float angle)
{
    this->sprite.setRotation(angle);
}

void sfml::SpriteSfml::rotate(float angle)
{
    this->sprite.rotate(angle);
}

void sfml::SpriteSfml::setTextureRect(const arcade::data::IntRect &rect)
{
    sf::IntRect sfRect{rect.left, rect.top, rect.width, rect.height};
    this->sprite.setTextureRect(sfRect);
}

arcade::data::IntRect sfml::SpriteSfml::getTextureRect() const
{
    sf::IntRect sfRect = this->sprite.getTextureRect();
    return arcade::data::IntRect{sfRect.top, sfRect.left, sfRect.width, sfRect.height};
}

void sfml::SpriteSfml::setColor(arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
    (void)asciiColors;
    sf::Color sfColor{color.r, color.g, color.b, color.a};
    this->sprite.setColor(sfColor);
}

sf::Sprite &sfml::SpriteSfml::getSfSprite()
{
    return this->sprite;
}
