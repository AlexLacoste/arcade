/*
** EPITECH PROJECT, 2021
** ubuntu [Container ubuntu:latest (/hungry_bose)]
** File description:
** Menu
*/

#include <iostream>
#include "Arcade.hpp"

void arcade::Arcade::handleMenu()
{
    this->handleMenuEvent();
    if (this->isClosed)
        return;
    this->graphicLib->clearWindow();
    for (auto &sprite : this->vectorSprite) {
        this->graphicLib->draw(sprite);
    }
    for (auto &text : this->vectorText) {
        this->graphicLib->draw(text);
    }
    this->graphicLib->display();
}

void arcade::Arcade::handleMenuEvent()
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
                    this->switchPreviousGraphicLib();
                    return;
                case ('s'):
                    this->switchNextGraphicLib();
                    return;
                // case ('A'):
                //     std::cout << "A" << std::endl;
                //     break;
            }
            switch (static_cast<int>(event.keyCode)) {
            //     case (arcade::data::RIGHT):
            //         this->vectorSprite.at(0)->move(arcade::data::Vector2f{
            //             static_cast<float>(this->graphicLib->getWindowSize().x * 0.5 / 100), 0});
            //         break;
            //     case (arcade::data::LEFT):
            //         this->vectorSprite.at(0)->move(arcade::data::Vector2f{
            //             static_cast<float>(-(this->graphicLib->getWindowSize().x * 0.5 / 100)), 0});
            //         break;
            //     case (arcade::data::UP):
            //         this->vectorSprite.at(0)->move(arcade::data::Vector2f{
            //             0, static_cast<float>(-(this->graphicLib->getWindowSize().y * 0.5 / 100))});
            //         break;
            //     case (arcade::data::DOWN):
            //         this->vectorSprite.at(0)->move(arcade::data::Vector2f{
            //             0, static_cast<float>(this->graphicLib->getWindowSize().y * 0.5 / 100)});
            //         break;
                case (arcade::data::ESCAPE):
                    this->isClosed = true;
                    return;
            }
        }
        // if (event.type == arcade::data::EventType::MOUSE_PRESSED) {
        //     if (event.btn == arcade::data::BTN_1) {
        //         std::cout << event.x << "    " << event.y << std::endl;
        //     }
        // }
    }
}

void arcade::Arcade::initMenu()
{
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorText.emplace_back(std::unique_ptr<displayer::IText>());

    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());

    std::unique_ptr<displayer::IText> &textKeyActions = this->vectorText.at(0);
    std::unique_ptr<displayer::IText> &textPreviousLib = this->vectorText.at(1);
    std::unique_ptr<displayer::IText> &textNextLib = this->vectorText.at(2);
    std::unique_ptr<displayer::IText> &textPreviousGame = this->vectorText.at(3);
    std::unique_ptr<displayer::IText> &textNextGame = this->vectorText.at(4);
    std::unique_ptr<displayer::IText> &textRestart = this->vectorText.at(5);
    std::unique_ptr<displayer::IText> &textGoMenu = this->vectorText.at(6);
    std::unique_ptr<displayer::IText> &textExit = this->vectorText.at(7);

    std::unique_ptr<displayer::ISprite> &boxGraphicLib = this->vectorSprite.at(0);
    std::unique_ptr<displayer::ISprite> &boxGameLib = this->vectorSprite.at(1);
    std::unique_ptr<displayer::ISprite> &boxScore = this->vectorSprite.at(2);
    std::unique_ptr<displayer::ISprite> &boxUsername = this->vectorSprite.at(3);
    std::unique_ptr<displayer::ISprite> &boxKeyAction = this->vectorSprite.at(4);
    std::vector<std::string> boxLibNcurse{this->createSquare(18, 27, false, '#')};
    std::vector<std::string> boxScoreNcurses{this->createSquare(10, 53, false, '#')};
    std::vector<std::string> boxUsernameNcurses{this->createSquare(8, 54, false, '#')};
    std::vector<std::string> boxkeyActionNcurses{this->createSquare(24, 43, false, '#')};

    std::vector<std::vector<arcade::data::Color>> spriteColorLibNcurses{colorSprite(18, 27, arcade::data::Color::Red)};
    std::vector<std::vector<arcade::data::Color>> spriteColorScoreNcurses{colorSprite(10, 53, arcade::data::Color::Blue)};
    std::vector<std::vector<arcade::data::Color>> spriteColorUsernameNcurses{colorSprite(8, 54, arcade::data::Color::Cyan)};
    std::vector<std::vector<arcade::data::Color>> spriteColorActionNcurses{colorSprite(24, 43, arcade::data::Color::Magenta)};

    textKeyActions = this->graphicLib->createText("Keys Action :");
    textKeyActions->setFont("ressources/font.ttf");
    textKeyActions->setColor(arcade::data::Color::White);
    textKeyActions->setCharacterSize(17);
    textKeyActions->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 86 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 62 / 100});

    textPreviousLib = this->graphicLib->createText("\"q\" : previous graphic library");
    textPreviousLib->setFont("ressources/font.ttf");
    textPreviousLib->setColor(arcade::data::Color::White);
    textPreviousLib->setCharacterSize(17);
    textPreviousLib->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 70 / 100});

    textNextLib = this->graphicLib->createText("\"s\" : next graphic library");
    textNextLib->setFont("ressources/font.ttf");
    textNextLib->setColor(arcade::data::Color::White);
    textNextLib->setCharacterSize(17);
    textNextLib->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 74 / 100});

    textPreviousGame = this->graphicLib->createText("\"w\" : previous game");
    textPreviousGame->setFont("ressources/font.ttf");
    textPreviousGame->setColor(arcade::data::Color::White);
    textPreviousGame->setCharacterSize(17);
    textPreviousGame->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 78 / 100});

    textNextGame = this->graphicLib->createText("\"w\" : next game");
    textNextGame->setFont("ressources/font.ttf");
    textNextGame->setColor(arcade::data::Color::White);
    textNextGame->setCharacterSize(17);
    textNextGame->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 82 / 100});

    textRestart = this->graphicLib->createText("\"r\" : restart the game");
    textRestart->setFont("ressources/font.ttf");
    textRestart->setColor(arcade::data::Color::White);
    textRestart->setCharacterSize(17);
    textRestart->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 86 / 100});

    textGoMenu = this->graphicLib->createText("\"m\" : go back menu");
    textGoMenu->setFont("ressources/font.ttf");
    textGoMenu->setColor(arcade::data::Color::White);
    textGoMenu->setCharacterSize(17);
    textGoMenu->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 90 / 100});

    textExit = this->graphicLib->createText("\"ESCAPE\" : exit");
    textExit->setFont("ressources/font.ttf");
    textExit->setColor(arcade::data::Color::White);
    textExit->setCharacterSize(17);
    textExit->setPosition(
        arcade::data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 94 / 100});

    boxGraphicLib = this->graphicLib->createSprite(
        "ressources/cadre.png", boxLibNcurse, arcade::data::Vector2f{0.4, 0.4});
    boxGraphicLib->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxGraphicLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 10 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 12 / 100});
    boxGraphicLib->setColor(arcade::data::Color::Red, spriteColorLibNcurses);

    boxGameLib = this->graphicLib->createSprite(
        "ressources/cadre.png", boxLibNcurse, arcade::data::Vector2f{0.4, 0.4});
    boxGameLib->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxGameLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 75 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 12 / 100});
    boxGameLib->setColor(arcade::data::Color::Red, spriteColorLibNcurses);

    boxScore = this->graphicLib->createSprite(
        "ressources/cadre.png", boxScoreNcurses, arcade::data::Vector2f{0.8, 0.3});
    boxScore->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxScore->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 37 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 7 / 100});
    boxScore->setColor(arcade::data::Color::Blue, spriteColorScoreNcurses);

    boxUsername = this->graphicLib->createSprite(
        "ressources/cadre.png", boxUsernameNcurses, arcade::data::Vector2f{0.8, 0.15});
    boxUsername->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxUsername->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 37 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 70 / 100});
    boxUsername->setColor(arcade::data::Color::Cyan, spriteColorUsernameNcurses);
    
    boxKeyAction = this->graphicLib->createSprite(
        "ressources/cadre.png", boxkeyActionNcurses, arcade::data::Vector2f{0.62, 0.36});
    boxKeyAction->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxKeyAction->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 80 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 60 / 100});
    boxKeyAction->setColor(arcade::data::Color::Magenta, spriteColorActionNcurses);
}