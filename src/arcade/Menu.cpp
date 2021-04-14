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
    if (this->isClosed)
        return;
    this->graphicLib->clearWindow();
    for (auto &text : this->vectorTextGame) {
        text->setColor(arcade::data::Color::White);
    }
    for (auto &text : this->vectorTextLib) {
        text->setColor(arcade::data::Color::White);
    }
    if (this->isChooseGame) {
        this->vectorTextGame.at(this->posChooseGame)->setColor(arcade::data::Color::Yellow);
    } else {
        this->vectorTextLib.at(this->posChooseGraphic)->setColor(arcade::data::Color::Yellow);
    }
    for (auto &sprite : this->vectorSprite) {
        this->graphicLib->draw(sprite);
    }
    this->iTextUsername->setText(this->username);
    this->graphicLib->draw(this->iTextUsername);
    for (auto &text : this->vectorTextInit) {
        this->graphicLib->draw(text);
    }
    for (auto &text : this->vectorTextLib) {
        this->graphicLib->draw(text);
    }
    for (auto &text : this->vectorTextGame) {
        this->graphicLib->draw(text);
    }
}

void arcade::Arcade::initMenu()
{
    this->initTextMenu();
    this->initSpriteMenu();
}

void arcade::Arcade::initTextMenu()
{
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());
    this->vectorTextInit.emplace_back(std::unique_ptr<displayer::IText>());

    std::unique_ptr<displayer::IText> &textKeyActions = this->vectorTextInit.at(0);
    std::unique_ptr<displayer::IText> &textPreviousLib = this->vectorTextInit.at(1);
    std::unique_ptr<displayer::IText> &textNextLib = this->vectorTextInit.at(2);
    std::unique_ptr<displayer::IText> &textPreviousGame = this->vectorTextInit.at(3);
    std::unique_ptr<displayer::IText> &textNextGame = this->vectorTextInit.at(4);
    std::unique_ptr<displayer::IText> &textRestart = this->vectorTextInit.at(5);
    std::unique_ptr<displayer::IText> &textGoMenu = this->vectorTextInit.at(6);
    std::unique_ptr<displayer::IText> &textExit = this->vectorTextInit.at(7);
    std::unique_ptr<displayer::IText> &textFisrt = this->vectorTextInit.at(8);
    std::unique_ptr<displayer::IText> &textSecond = this->vectorTextInit.at(9);
    std::unique_ptr<displayer::IText> &textThird = this->vectorTextInit.at(10);
    std::unique_ptr<displayer::IText> &textUsername = this->vectorTextInit.at(11);

    textKeyActions = this->graphicLib->createText("Keys Action :");
    textKeyActions->setFont("ressources/font.ttf");
    textKeyActions->setColor(arcade::data::Color::White);
    textKeyActions->setCharacterSize(17);
    textKeyActions->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 86 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 62 / 100});

    textPreviousLib = this->graphicLib->createText("\".\" : previous graphic library");
    textPreviousLib->setFont("ressources/font.ttf");
    textPreviousLib->setColor(arcade::data::Color::White);
    textPreviousLib->setCharacterSize(17);
    textPreviousLib->setPosition(
        {static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 70 / 100});

    textNextLib = this->graphicLib->createText("\"/\" : next graphic library");
    textNextLib->setFont("ressources/font.ttf");
    textNextLib->setColor(arcade::data::Color::White);
    textNextLib->setCharacterSize(17);
    textNextLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 74 / 100});

    textPreviousGame = this->graphicLib->createText("\"w\" : previous game");
    textPreviousGame->setFont("ressources/font.ttf");
    textPreviousGame->setColor(arcade::data::Color::White);
    textPreviousGame->setCharacterSize(17);
    textPreviousGame->setPosition(
        {static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 78 / 100});

    textNextGame = this->graphicLib->createText("\"x\" : next game");
    textNextGame->setFont("ressources/font.ttf");
    textNextGame->setColor(arcade::data::Color::White);
    textNextGame->setCharacterSize(17);
    textNextGame->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 82 / 100});

    textRestart = this->graphicLib->createText("\"r\" : restart the game");
    textRestart->setFont("ressources/font.ttf");
    textRestart->setColor(arcade::data::Color::White);
    textRestart->setCharacterSize(17);
    textRestart->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 86 / 100});

    textGoMenu = this->graphicLib->createText("\"m\" : go back menu");
    textGoMenu->setFont("ressources/font.ttf");
    textGoMenu->setColor(arcade::data::Color::White);
    textGoMenu->setCharacterSize(17);
    textGoMenu->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 90 / 100});

    textExit = this->graphicLib->createText("\"ESCAPE\" : exit");
    textExit->setFont("ressources/font.ttf");
    textExit->setColor(arcade::data::Color::White);
    textExit->setCharacterSize(17);
    textExit->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 81 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 94 / 100});

    textFisrt = this->graphicLib->createText("1.");
    textFisrt->setFont("ressources/font.ttf");
    textFisrt->setColor(arcade::data::Color::White);
    textFisrt->setCharacterSize(17);
    textFisrt->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 39 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 12 / 100});

    textSecond = this->graphicLib->createText("2.");
    textSecond->setFont("ressources/font.ttf");
    textSecond->setColor(arcade::data::Color::White);
    textSecond->setCharacterSize(17);
    textSecond->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 39 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});

    textThird = this->graphicLib->createText("3.");
    textThird->setFont("ressources/font.ttf");
    textThird->setColor(arcade::data::Color::White);
    textThird->setCharacterSize(17);
    textThird->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 39 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 28 / 100});

    textUsername = this->graphicLib->createText("User :");
    textUsername->setFont("ressources/font.ttf");
    textUsername->setColor(arcade::data::Color::White);
    textUsername->setCharacterSize(17);
    textUsername->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 40 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 77 / 100});

    this->iTextUsername = this->graphicLib->createText("user____");
    this->iTextUsername->setFont("ressources/font.ttf");
    this->iTextUsername->setColor(arcade::data::Color::White);
    this->iTextUsername->setCharacterSize(17);
    this->iTextUsername->setPosition(
        {static_cast<float>(this->graphicLib->getWindowSize().x) * 44 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 77 / 100});

    this->initTextLib();
}

void arcade::Arcade::initTextLib()
{
    std::size_t i = 0;

    for (const auto &grapLib : this->libs) {
        this->vectorTextLib.emplace_back(std::unique_ptr<displayer::IText>());
        std::unique_ptr<displayer::IText> &text = this->vectorTextLib.at(i);
        text = this->graphicLib->createText(grapLib);
        text->setFont("ressources/font.ttf");
        text->setColor(arcade::data::Color::White);
        text->setCharacterSize(17);
        text->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 11 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 15 / 100
                + static_cast<float>(this->graphicLib->getWindowSize().y) * i * 6 / 100});
        i++;
    }
    i = 0;
    for (const auto &gameLib : this->libsGame) {
        this->vectorTextGame.emplace_back(std::unique_ptr<displayer::IText>());
        std::unique_ptr<displayer::IText> &text = this->vectorTextGame.at(i);
        text = this->graphicLib->createText(gameLib);
        text->setFont("ressources/font.ttf");
        text->setColor(arcade::data::Color::White);
        text->setCharacterSize(17);
        text->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 76 / 100,
            static_cast<float>(this->graphicLib->getWindowSize().y) * 15 / 100
                + static_cast<float>(this->graphicLib->getWindowSize().y) * i * 6 / 100});
        i++;
    }
}

void arcade::Arcade::initSpriteMenu()
{
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
    this->vectorSprite.emplace_back(std::unique_ptr<displayer::ISprite>());

    std::unique_ptr<displayer::ISprite> &boxGraphicLib = this->vectorSprite.at(0);
    std::unique_ptr<displayer::ISprite> &boxGameLib = this->vectorSprite.at(1);
    std::unique_ptr<displayer::ISprite> &boxScore = this->vectorSprite.at(2);
    std::unique_ptr<displayer::ISprite> &boxUsername = this->vectorSprite.at(3);
    std::unique_ptr<displayer::ISprite> &boxKeyAction = this->vectorSprite.at(4);
    std::vector<std::string> boxLibNcurse{this->createSquare(18, 27, false, '#')};
    std::vector<std::string> boxScoreNcurses{this->createSquare(18, 53, false, '#')};
    std::vector<std::string> boxUsernameNcurses{this->createSquare(8, 54, false, '#')};
    std::vector<std::string> boxkeyActionNcurses{this->createSquare(24, 43, false, '#')};

    std::vector<std::vector<arcade::data::Color>> spriteColorLibNcurses{
        colorSprite(18, 27, arcade::data::Color::Red)};
    std::vector<std::vector<arcade::data::Color>> spriteColorScoreNcurses{
        colorSprite(18, 53, arcade::data::Color::Blue)};
    std::vector<std::vector<arcade::data::Color>> spriteColorUsernameNcurses{
        colorSprite(8, 54, arcade::data::Color::Green)};
    std::vector<std::vector<arcade::data::Color>> spriteColorActionNcurses{
        colorSprite(24, 43, arcade::data::Color::Magenta)};

    boxGraphicLib = this->graphicLib->createSprite(
        "ressources/cadre.bmp", boxLibNcurse, arcade::data::Vector2f{0.5, 0.4});
    boxGraphicLib->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxGraphicLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 10 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 12 / 100});
    boxGraphicLib->setColor(arcade::data::Color::Red, spriteColorLibNcurses);

    boxGameLib = this->graphicLib->createSprite(
        "ressources/cadre.bmp", boxLibNcurse, arcade::data::Vector2f{0.5, 0.4});
    boxGameLib->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxGameLib->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 75 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 12 / 100});
    boxGameLib->setColor(arcade::data::Color::Red, spriteColorLibNcurses);

    boxScore = this->graphicLib->createSprite(
        "ressources/cadre.bmp", boxScoreNcurses, arcade::data::Vector2f{0.8, 0.3});
    boxScore->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxScore->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 37 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 7 / 100});
    boxScore->setColor(arcade::data::Color::Blue, spriteColorScoreNcurses);

    boxUsername = this->graphicLib->createSprite(
        "ressources/cadre.bmp", boxUsernameNcurses, arcade::data::Vector2f{0.8, 0.15});
    boxUsername->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxUsername->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 37 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 70 / 100});
    boxUsername->setColor(arcade::data::Color::Green, spriteColorUsernameNcurses);

    boxKeyAction = this->graphicLib->createSprite(
        "ressources/cadre.bmp", boxkeyActionNcurses, arcade::data::Vector2f{0.62, 0.36});
    boxKeyAction->setTextureRect(arcade::data::IntRect{32, 65, 590, 1102});
    boxKeyAction->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 80 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 60 / 100});
    boxKeyAction->setColor(arcade::data::Color::Magenta, spriteColorActionNcurses);
}

void arcade::Arcade::addCharToUsername(char c)
{
    if (this->realUsername.size() == 8) {
        return;
    }
    this->realUsername.push_back(c);
    for (int i = 0; i < this->username.size(); i++) {
        if (this->username.at(i) == '_') {
            this->username.at(i) = c;
            break;
        }
    }
}

void arcade::Arcade::deleteOneCharUsername()
{
    int i = 0;

    if (this->realUsername.size() == 0) {
        return;
    }
    for (; i < this->username.size() && this->username.at(i) != '_'; i++);
    this->username.at(i - 1) = '_';
    this->realUsername.pop_back();
}