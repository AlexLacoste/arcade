/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unistd.h>
#include "../shared/Color.cpp"

arcade::Arcade::Arcade(const std::string &libGraphic)
{
    std::size_t i = 0;

    this->highScore = 0;
    this->getLib();
    for (i = 0; i < this->libs.size() && this->libs.at(i).compare(libGraphic) != 0; i++);
    this->libPositionVector = i;
    this->gameLib = nullptr;
    this->graphicLib = nullptr;
    this->dlLoaderGame = nullptr;
    this->dlLoaderGraphic = std::make_unique<DLLoader>(libGraphic.c_str());
    this->graphicLibLoader();
    this->username = "";
    // this->gameTitle = getGameTitle();
    this->state = USERNAME;
    this->isClosed = false;
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::run()
{
    const std::unordered_map<State, void (arcade::Arcade::*)()> mapFptr{
        {USERNAME, &arcade::Arcade::handleUser}, {MENU, &arcade::Arcade::handleMenu},
        {GAME, &arcade::Arcade::handleGame}};
    std::unique_ptr<displayer::IText> textLib;
    std::unique_ptr<displayer::ISprite> spriteLib;
    std::vector<std::string> spriteNcurse;
    std::vector<std::vector<arcade::data::Color>> spriteColorNcurse;

    this->graphicLib->init("Arcade");
    textLib = this->graphicLib->createText("c'est un test");
    textLib->setFont("ressources/font.ttf");
    textLib->setColor(arcade::data::Color::Red);
    textLib->setCharacterSize(40);
    textLib->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 20 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});
    this->vectorText.emplace_back(std::move(textLib));
    spriteLib = this->graphicLib->createSprite("ressources/pacman.png", spriteNcurse, arcade::data::Vector2f{0.08, 0.08});
    spriteLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 30 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 30 / 100});
    spriteLib->setTextureRect(arcade::data::IntRect{0, 0, 1200, 1270});
    spriteLib->setColor(arcade::data::Color(255, 255, 255, 128), spriteColorNcurse);
    this->vectorSprite.emplace_back(std::move(spriteLib));
    while (this->graphicLib->isOpen()) {
        if (this->state != CLOSED) {
            (this->*mapFptr.at(this->state))();
        }
        if (this->isClosed) {
            break;
        }
    }
    this->graphicLib->stop();
}

void arcade::Arcade::graphicLibLoader()
{
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>();
}

void arcade::Arcade::gameLibLoader()
{
}

void arcade::Arcade::switchGraphicLib()
{
    this->graphicLib->stop();
    std::unique_ptr<displayer::IText> textLib;

    this->libPositionVector =
        (this->libPositionVector + 1 < this->libs.size()) ? this->libPositionVector + 1 : 0;
    this->vectorText.clear();
    this->dlLoaderGraphic = std::make_unique<DLLoader>(this->libs.at(this->libPositionVector).c_str());
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>(); 
    this->graphicLib->init("Arcade");
    textLib = this->graphicLib->createText("c'est un test");
    textLib->setFont("ressources/font.ttf");
    textLib->setColor(arcade::data::Color::Red);
    textLib->setCharacterSize(40);
    textLib->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 20 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});
    this->vectorText.emplace_back(std::move(textLib));
}

void arcade::Arcade::getLib()
{
    for (const auto &file : std::filesystem::directory_iterator("lib")) {
        std::string tmp = file.path();
        std::cout << tmp << std::endl;
        if (tmp.find_last_of(".so"))
            this->libs.push_back(tmp);
    }
}

void arcade::Arcade::handleUser()
{
    this->handleUserEvent();
    if (this->isClosed)
        return;
    this->graphicLib->clearWindow();
    for (auto &text : this->vectorText) {
        this->graphicLib->draw(text);
    }
    for (auto &sprite : this->vectorSprite) {
        this->graphicLib->draw(sprite);
    }
    this->graphicLib->display();
}

void arcade::Arcade::handleUserEvent()
{
    std::vector<arcade::data::Event> events = this->graphicLib->getEvents();
    for (auto event : events) {
        if (event.type == arcade::data::WINDOW_CLOSED) {
            this->isClosed = true;
            return;
        }
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            switch (event.key) {
                case ('q'):
                    this->switchGraphicLib();
                    return;
            }
            switch (static_cast<int>(event.keyCode)) {
                case (arcade::data::RIGHT):
                    this->vectorSprite.at(0)->move(arcade::data::Vector2f{10, 0});
                    break;
                case (arcade::data::LEFT):
                    this->vectorSprite.at(0)->move(arcade::data::Vector2f{-10, 0});
                    break;
                case (arcade::data::UP):
                    this->vectorSprite.at(0)->move(arcade::data::Vector2f{0, -10});
                    break;
                case (arcade::data::DOWN):
                    this->vectorSprite.at(0)->move(arcade::data::Vector2f{0, 10});
                    break;
                case (arcade::data::ESCAPE):
                    this->isClosed = true;
                    return;
            }
        }

    }
}

void arcade::Arcade::handleMenu()
{
}

void arcade::Arcade::handleMenuEvent()
{
}

void arcade::Arcade::handleGame()
{
}

void arcade::Arcade::handleGameEvent()
{
}
