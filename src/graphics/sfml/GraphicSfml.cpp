/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
#include "Sfml.hpp"

extern "C" std::unique_ptr<sfml::GraphicSfml> entry_point()
{
    return std::make_unique<sfml::GraphicSfml>();
}

sfml::GraphicSfml::GraphicSfml()
{
}

sfml::GraphicSfml::~GraphicSfml()
{
    if (this->window.isOpen())
        this->window.close();
}

bool sfml::GraphicSfml::isOpen() const
{
    return this->window.isOpen();
}

void sfml::GraphicSfml::init(const std::string &title, const unsigned int limit)
{
    this->window.create(sf::VideoMode(1920, 1080, 32), title);
    this->window.setFramerateLimit(limit);
    this->time = this->clock.getElapsedTime();
}

void sfml::GraphicSfml::display()
{
    this->window.display();
    this->events.clear();
}

void sfml::GraphicSfml::stop()
{
    this->window.close();
}

void sfml::GraphicSfml::clearWindow()
{
    this->window.clear();
}

void sfml::GraphicSfml::restartClock()
{
}

double sfml::GraphicSfml::getDeltaTime()
{
    return this->time.asSeconds();
}

arcade::data::Vector2u sfml::GraphicSfml::getWindowSize()
{
    return arcade::data::Vector2u{this->window.getSize().x, this->window.getSize().y};
}

std::vector<arcade::data::Event> sfml::GraphicSfml::getEvents()
{
    while (this->window.pollEvent(this->event)) {
        this->events.emplace_back(arcade::data::EventType::KEY_PRESSED,
            static_cast<arcade::data::KeyCode>(this->event.key.code));
    }
    return this->events;
}

void sfml::GraphicSfml::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    this->window.draw(reinterpret_cast<std::unique_ptr<TextSfml> &>(text)->getSfText());
}

std::unique_ptr<arcade::displayer::IText> sfml::GraphicSfml::createText(const std::string &text)
{
    return std::make_unique<TextSfml>(text);
}

std::unique_ptr<arcade::displayer::IText> sfml::GraphicSfml::createText()
{
    return std::make_unique<TextSfml>();
}