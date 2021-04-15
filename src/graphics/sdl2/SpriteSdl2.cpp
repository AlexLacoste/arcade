/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** SpriteSdl2
*/

#include <iostream>
#include "Sdl2.hpp"
#include "../../shared/Errors.hpp"

sdl2::SpriteSdl2::SpriteSdl2() : texture(nullptr)
{
}

sdl2::SpriteSdl2::SpriteSdl2(const std::string &spritePath,
    const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale) : texture(nullptr)
{
    this->setSprite(spritePath, asciiSprite);
    this->setScale(scale);
}

sdl2::SpriteSdl2::~SpriteSdl2()
{
    SDL_DestroyTexture(this->texture);
}

void sdl2::SpriteSdl2::setSprite(
    const std::string &spritePath, const std::vector<std::string> &asciiSprite)
{
    (void)asciiSprite;
    SDL_Surface *image = SDL_LoadBMP(spritePath.c_str());
    if (!image) {
        throw arcade::errors::Error("SDL load image");
    }
    this->texture = SDL_CreateTextureFromSurface(sdl2::GraphicSdl2::renderer, image);
    if (!this->texture) {
        throw arcade::errors::Error("SDL create texture sprite");
    }
    this->srcRect.x = 0;
    this->srcRect.y = 0;
    if (SDL_QueryTexture(this->texture, NULL, NULL, &this->srcRect.w, &this->srcRect.h)) {
        throw arcade::errors::Error("SDL query texture");
    }
    this->destRect = {0, 0, this->srcRect.w, this->srcRect.h};
    this->size = {static_cast<float>(this->srcRect.w), static_cast<float>(this->srcRect.h)};
    this->scale = {1, 1};
    this->rotation = 0;
    this->origin = {0, 0};
    SDL_FreeSurface(image);
}

void sdl2::SpriteSdl2::setPosition(arcade::data::Vector2f pos)
{
    this->destRect.x = pos.x - this->origin.x;
    this->destRect.y = pos.y - this->origin.y;
}

arcade::data::Vector2f sdl2::SpriteSdl2::getPosition() const
{
    return arcade::data::Vector2f{static_cast<float>(this->destRect.x + this->origin.x),
        static_cast<float>(this->destRect.y + this->origin.y)};
}

void sdl2::SpriteSdl2::move(arcade::data::Vector2f pos)
{
    this->destRect = {static_cast<int>(this->destRect.x + pos.x),
        static_cast<int>(this->destRect.y + pos.y), this->destRect.w, this->destRect.h};
}

void sdl2::SpriteSdl2::move(float x, float y)
{
    this->destRect = {static_cast<int>(this->destRect.x + x),
        static_cast<int>(this->destRect.y + y), this->destRect.w, this->destRect.h};
}

void sdl2::SpriteSdl2::setOrigin(arcade::data::Vector2f origin)
{
    this->destRect = {static_cast<int>(this->destRect.x + this->origin.x),
        static_cast<int>(this->destRect.y + this->origin.y), this->destRect.w, this->destRect.h};
    this->origin = SDL_Point{static_cast<int>(origin.x), static_cast<int>(origin.y)};
    this->origin = {static_cast<int>(this->origin.x * this->scale.x), static_cast<int>(this->origin.y * this->scale.y)};
    this->destRect = {static_cast<int>(this->destRect.x - this->origin.x),
        static_cast<int>(this->destRect.y - this->origin.y), this->destRect.w, this->destRect.h};
}

arcade::data::Vector2f sdl2::SpriteSdl2::getOrigin() const
{
    return {this->origin.x * this->scale.x, this->origin.y * this->scale.y};
}

arcade::data::FloatRect sdl2::SpriteSdl2::getLocalBounds() const
{
    return arcade::data::FloatRect{0, 0, this->size.x, this->size.y};
}

arcade::data::FloatRect sdl2::SpriteSdl2::getGlobalBounds() const
{
    return arcade::data::FloatRect{
        this->destRect.y, this->destRect.x, this->destRect.w, this->destRect.h};
}

void sdl2::SpriteSdl2::setScale(arcade::data::Vector2f scale)
{
    this->origin = {static_cast<int>(this->origin.x / this->scale.x), static_cast<int>(this->origin.y / this->scale.y)};
    this->scale = scale;
    this->origin = {static_cast<int>(this->origin.x * this->scale.x), static_cast<int>(this->origin.y * this->scale.y)};
    this->destRect = {this->destRect.x,
        this->destRect.y, static_cast<int>(this->destRect.w  * this->scale.x), static_cast<int>(this->destRect.h  * this->scale.y)};
}

arcade::data::Vector2f sdl2::SpriteSdl2::getScale() const
{
    return this->scale;
}

float sdl2::SpriteSdl2::getRotation() const
{
    return this->rotation;
}

void sdl2::SpriteSdl2::setRotation(float angle)
{
    this->rotation = angle;
}

void sdl2::SpriteSdl2::rotate(float angle)
{
    this->rotation += angle;
}

void sdl2::SpriteSdl2::setTextureRect(const arcade::data::IntRect &rect)
{
    this->srcRect = {rect.left, rect.top, rect.width, rect.height};
}

arcade::data::IntRect sdl2::SpriteSdl2::getTextureRect() const
{
    return arcade::data::IntRect{
        this->srcRect.y, this->srcRect.x, this->srcRect.w, this->srcRect.h};
}

void sdl2::SpriteSdl2::setColor(
    arcade::data::Color color, const std::vector<std::vector<arcade::data::Color>> &asciiColors)
{
    (void)asciiColors;
    SDL_SetTextureColorMod(this->texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(this->texture, color.a);
}

void sdl2::SpriteSdl2::drawSprite()
{
    if (SDL_RenderCopyEx(sdl2::GraphicSdl2::renderer, this->texture, &this->srcRect,
            &this->destRect, this->rotation, &this->origin, SDL_FLIP_NONE)
        != 0) {
        throw arcade::errors::Error("SDL draw sprite");
    }
}