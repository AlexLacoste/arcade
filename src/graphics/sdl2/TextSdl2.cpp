/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** TextSdl2
*/

#include <iostream>
#include "Sdl2.hpp"
#include <SDL2/SDL_ttf.h>

sdl2::TextSdl2::TextSdl2()
{
}

sdl2::TextSdl2::TextSdl2(const std::string &text)
{
    this->setText(text);
}

sdl2::TextSdl2::~TextSdl2()
{
}

void sdl2::TextSdl2::setText(const std::string &text)
{
    this->text = text;
    if (!this->font) {
        return;
    }
    SDL_Surface *surface = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
    if (!surface) {
        // throw error
    }
    this->texture = create_texture(SDL_CreateTextureFromSurface(sdl2::GraphicSdl2::renderer.get(), surface));
    if (!this->texture) {
        // throw error;
    }
    if (SDL_QueryTexture(this->texture.get(), NULL, NULL, &this->destRect.w, &this->destRect.h) != 0) {
        // throw error;
    }
    SDL_FreeSurface(surface);

}

std::string sdl2::TextSdl2::getText() const
{
    return this->text;
}

void sdl2::TextSdl2::setPosition(arcade::data::Vector2f pos)
{
    this->destRect = {static_cast<int>(pos.x + this->origin.x), static_cast<int>(pos.y + this->origin.y), this->destRect.w, this->destRect.h};
}

arcade::data::Vector2f sdl2::TextSdl2::getPosition() const
{
    return arcade::data::Vector2f{this->destRect.x + this->origin.x, this->destRect.y + this->origin.y};
}

void sdl2::TextSdl2::setFont(const std::string &font)
{
    this->fontPath = font;
    this->font = create_font(TTF_OpenFont(this->fontPath.c_str(), this->size));
    if (!this->font) {
        // throw error
    }
    this->setText(this->text);
}

void sdl2::TextSdl2::setColor(arcade::data::Color color)
{
    this->color = SDL_Color{color.r, color.g, color.b, color.a};
    this->setText(this->text);
}

arcade::data::Color sdl2::TextSdl2::getColor() const
{
    return arcade::data::Color{this->color.r, this->color.g, this->color.b, this->color.a};
}

void sdl2::TextSdl2::setCharacterSize(unsigned int size)
{
    this->size = size;
    if (!this->fontPath.empty()) {
        this->setFont(this->fontPath);
    }
}

arcade::data::FloatRect sdl2::TextSdl2::getLocalBounds() const
{
    return arcade::data::FloatRect{0, 0, this->destRect.w, this->destRect.h};
}

arcade::data::FloatRect sdl2::TextSdl2::getGlobalBounds() const
{
    return arcade::data::FloatRect{this->destRect.y, this->destRect.x, this->destRect.w, this->destRect.h};
}

void sdl2::TextSdl2::setOrigin(arcade::data::Vector2f origin)
{
    this->destRect = {static_cast<int>(this->destRect.x + this->origin.x), static_cast<int>(this->destRect.y + this->origin.y), this->destRect.w, this->destRect.h};
    this->origin = origin;
    this->destRect = {static_cast<int>(this->destRect.x - this->origin.x), static_cast<int>(this->destRect.y - this->origin.y), this->destRect.w, this->destRect.h};
}

arcade::data::Vector2f sdl2::TextSdl2::getOrigin() const
{
    return this->origin;
}

void sdl2::TextSdl2::drawText()
{
    if (!this->texture) {
        return;
    }
    if (SDL_RenderCopy(sdl2::GraphicSdl2::renderer.get(), this->texture.get(), NULL, &this->destRect) != 0) {
        // throw error;
    }
}
