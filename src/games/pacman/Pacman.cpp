/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

#include "Pacman.hpp"

extern "C" std::unique_ptr<arcade::games::IGame> entry_point()
{
    return std::make_unique<arcade::pacman::Pacman>();
}

arcade::pacman::Pacman::Pacman()
{
}

arcade::pacman::Pacman::~Pacman()
{
}

void arcade::pacman::Pacman::init(std::shared_ptr<displayer::IDisplay> &disp)
{
    std::srand(std::time(nullptr));
    this->graphicLib = disp;
    this->playerScore = 0;
    this->enemiesClock = std::chrono::high_resolution_clock::now();
    this->gameMap = this->createGameMap("ressources/pacman/pacman_map.txt");
    this->createPlayer();
    this->createTexts();
    std::for_each(this->gameStorage.begin(), this->gameStorage.end(), [&](std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element) {
      if (element.first.getCharacter() == 'D') {
          this->previousEnemiesMove.push_back(2);
      }
    });
}
arcade::games::GameStatus arcade::pacman::Pacman::update()
{
    this->handleEvents();
    this->updateTexts();
    this->eatPacgums();
    std::for_each(this->gameStorage.begin(), this->gameStorage.end(), [&](std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element) {
        this->graphicLib->draw(element.second);
    });
    std::for_each(this->gameTexts.begin(), this->gameTexts.end(), [&](std::unique_ptr<displayer::IText> &text) {
      this->graphicLib->draw(text);
    });
    this->graphicLib->draw(playerSprite);
    if (this->getTimeDelay() > 0.3) {
        this->moveEnemies();
    }
    if (this->pacmanDamage() == 1) {
        return arcade::games::GAME_ENDED;
    }
    return arcade::games::PLAYING;
}

void arcade::pacman::Pacman::stop()
{
    this->gameStorage.clear();
    this->gameMap.clear();
    this->gameTexts.clear();
    this->previousEnemiesMove.clear();
}

void arcade::pacman::Pacman::restart()
{
    this->stop();
    this->init(this->graphicLib);
}

unsigned int arcade::pacman::Pacman::getScore() const
{
    return static_cast<unsigned int>(this->playerScore);
}

void arcade::pacman::Pacman::createPlayer(void)
{
    arcade::data::Vector2f position{13, 23};

    /* CREATE PLAYER PIXEL */
    arcade::pacman::Pixel pixel{'G', "ressources/pacman/pacman_l.bmp", position.x, position.y};

    pixel.setColor(arcade::data::Color{255, 255, 0});
    this->playerPixel = std::make_unique<Pixel>(pixel);

    /* CREATE PLAYER SPRITE */
    this->playerSprite = this->graphicLib->createSprite(this->playerPixel->getPixelImage(), std::vector<std::string>{std::string{this->playerPixel->getCharacter()}}, arcade::data::Vector2f{0.04, 0.04});
    this->playerSprite->setTextureRect(arcade::data::IntRect{0, 0, 500, 500});
    this->playerSprite->setColor(this->playerPixel->getPixelColor(), this->colorSprite(1, 1, this->playerPixel->getPixelColor()));
    this->playerSprite->setPosition(arcade::data::Vector2f{position.x * (this->playerSprite->getLocalBounds().width * this->playerSprite->getScale().x), position.y * (this->playerSprite->getLocalBounds().height * this->playerSprite->getScale().y)});
}

void arcade::pacman::Pacman::createTexts()
{
    this->gameTexts.push_back(std::unique_ptr<displayer::IText>());
    std::unique_ptr<displayer::IText> &textScore = this->gameTexts.back();

    textScore = this->graphicLib->createText("Score: " + std::to_string(this->playerScore));
    textScore->setFont("ressources/font.ttf");
    textScore->setColor(arcade::data::Color{255, 255, 255});
    textScore->setCharacterSize(17);
    textScore->setPosition({static_cast<float>(this->graphicLib->getWindowSize().x) * 35 / 100, static_cast<float>(this->graphicLib->getWindowSize().y) * 10 / 100});
}

void arcade::pacman::Pacman::handleEvents()
{
    std::vector<arcade::data::Event> events = this->graphicLib->getEvents();

    for (auto event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            switch (static_cast<int>(event.keyCode)) {
                case (arcade::data::UP):
                    this->movePlayer("ressources/pacman/pacman_u.bmp", arcade::data::Vector2i{0, -1});
                    break;
                case (arcade::data::DOWN):
                    this->movePlayer("ressources/pacman/pacman_d.bmp", arcade::data::Vector2i{0, 1});
                    break;
                case (arcade::data::LEFT):
                    this->movePlayer("ressources/pacman/pacman_l.bmp", arcade::data::Vector2i{-1, 0});
                    break;
                case (arcade::data::RIGHT):
                    this->movePlayer("ressources/pacman/pacman_r.bmp", arcade::data::Vector2i{1, 0});
                    break;
            }
        }
    }
}

void arcade::pacman::Pacman::updateTexts(void)
{
    this->gameTexts.at(0)->setText("Score: " + std::to_string(this->playerScore));
}

void arcade::pacman::Pacman::moveEnemies(void)
{
    int indexEnemie = 0;

    for (auto &element : this->gameStorage) {
        if (element.first.getCharacter() == 'D') {
            int randomNumber = std::rand() % 4;

            if (this->previousEnemiesMove.at(indexEnemie) != randomNumber) {
                switch (randomNumber) {
                    case 0:
                        this->moveOneEnemie(element, arcade::data::Vector2i{indexEnemie, randomNumber}, "ressources/pacman/ghost_r.bmp", arcade::data::Vector2i{0, -1});
                        break;
                    case 1:
                        this->moveOneEnemie(element, arcade::data::Vector2i{indexEnemie, randomNumber}, "ressources/pacman/ghost_r.bmp", arcade::data::Vector2i{1, 0});
                        break;
                    case 2:
                        this->moveOneEnemie(element, arcade::data::Vector2i{indexEnemie, randomNumber}, "ressources/pacman/ghost_r.bmp", arcade::data::Vector2i{0, 1});
                        break;
                    case 3:
                        this->moveOneEnemie(element, arcade::data::Vector2i{indexEnemie, randomNumber}, "ressources/pacman/ghost_r.bmp", arcade::data::Vector2i{-1, 0});
                        break;
                }
            }
            indexEnemie += 1;
        }
    }
}

void arcade::pacman::Pacman::moveOneEnemie(std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &enemie, arcade::data::Vector2i infoEnemie, std::string imagePath, arcade::data::Vector2i movement)
{
    float diffX = enemie.first.getPosX() + (movement.x);
    float diffY = enemie.first.getPosY() + (movement.y);
    char diffChar = this->getCharAtPos(arcade::data::Vector2f{diffX, diffY});

    if (diffChar != '#' && diffChar != 'D') {
        if (diffChar == '-') {
            if (enemie.first.getIsInMaze()) {
                return;
            }
            diffX -= 1;
            enemie.first.setIsInMaze(true);
        }
        this->checkPreviousEnemiesMove(infoEnemie);
        enemie.first.setPixelImage(imagePath);
        enemie.second->setSprite(enemie.first.getPixelImage(), std::vector<std::string>{std::string{enemie.first.getCharacter()}});
        enemie.second->setScale(arcade::data::Vector2f{0.04, 0.04});
        enemie.second->setPosition(arcade::data::Vector2f{enemie.first.getPosX() * (enemie.second->getLocalBounds().width * enemie.second->getScale().x), enemie.first.getPosY() * (enemie.second->getLocalBounds().height * enemie.second->getScale().y)});
        enemie.first.setPos(arcade::data::Vector2f{diffX, diffY});
        enemie.second->move((enemie.second->getLocalBounds().width * enemie.second->getScale().x) * (movement.x), (enemie.second->getLocalBounds().height * enemie.second->getScale().y) * (movement.y));
        this->restartClock();
    }
    if (diffChar == 'P') {
        this->onTeleportPointEnemie(enemie, arcade::data::Vector2f{diffX, diffY});
    }
}

void arcade::pacman::Pacman::checkPreviousEnemiesMove(arcade::data::Vector2i infoEnemie)
{
    if (infoEnemie.y == 0) {
        this->previousEnemiesMove.at(infoEnemie.x) = 2;
    }
    if (infoEnemie.y == 1) {
        this->previousEnemiesMove.at(infoEnemie.x) = 3;
    }
    if (infoEnemie.y == 2) {
        this->previousEnemiesMove.at(infoEnemie.x) = 0;
    }
    if (infoEnemie.y == 3) {
        this->previousEnemiesMove.at(infoEnemie.x) = 1;
    }
}

void arcade::pacman::Pacman::movePlayer(std::string imagePath, arcade::data::Vector2i movement)
{
    float diffX = this->playerPixel->getPosX() + (movement.x);
    float diffY = this->playerPixel->getPosY() + (movement.y);
    char diffChar = this->getCharAtPos(arcade::data::Vector2f{diffX, diffY});

    this->playerPixel->setPixelImage(imagePath);
    this->playerSprite->setSprite(this->playerPixel->getPixelImage(), std::vector<std::string>{std::string{this->playerPixel->getCharacter()}});
    this->playerSprite->setScale(arcade::data::Vector2f{0.04, 0.04});
    this->playerSprite->setPosition(arcade::data::Vector2f{this->playerPixel->getPosX() * (this->playerSprite->getLocalBounds().width * this->playerSprite->getScale().x), this->playerPixel->getPosY() * (this->playerSprite->getLocalBounds().height * this->playerSprite->getScale().y)});
    if (diffChar != '#' && diffChar != '-') {
        this->playerPixel->setPos(arcade::data::Vector2f{diffX, diffY});
        this->playerSprite->move((this->playerSprite->getLocalBounds().width * this->playerSprite->getScale().x) * (movement.x), (this->playerSprite->getLocalBounds().height * this->playerSprite->getScale().y) * (movement.y));
    }
    if (diffChar == 'P') {
        this->onTeleportPointPlayer(arcade::data::Vector2f{diffX, diffY});
    }
}

void arcade::pacman::Pacman::eatPacgums()
{
    char c = this->getCharAtPos(this->playerPixel->getPos());

    if (c == '.' || c == 'O') {
        auto itElement = std::find_if(this->gameStorage.begin(), this->gameStorage.end(), [&](std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element) {
          return (element.first.getPosX() == this->playerPixel->getPos().x) && (element.first.getPosY() == this->playerPixel->getPos().y);
        });

        this->gameStorage.erase(itElement);
        c == '.' ? this->playerScore += 100 : this->playerScore += 220;
    }
}

void arcade::pacman::Pacman::onTeleportPointEnemie(std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element, arcade::data::Vector2f pos)
{
    for (auto &mapElement : this->gameStorage) {
      if ((mapElement.first.getCharacter() == 'P') && ((mapElement.first.getPosX() != pos.x) || (mapElement.first.getPosY() != pos.y))) {
          element.second->setSprite(element.first.getPixelImage(), std::vector<std::string>{std::string{element.first.getCharacter()}});
          element.second->setScale(arcade::data::Vector2f{0.04, 0.04});
          element.first.setPos(mapElement.first.getPos());
          element.second->setPosition(arcade::data::Vector2f{element.first.getPosX() * (element.second->getLocalBounds().width * element.second->getScale().x), element.first.getPosY() * (element.second->getLocalBounds().height * element.second->getScale().y)});
      }
    }
}

void arcade::pacman::Pacman::onTeleportPointPlayer(data::Vector2f pos)
{
    for (auto &mapElement : this->gameStorage) {
      if ((mapElement.first.getCharacter() == 'P') && ((mapElement.first.getPosX() != pos.x) || (mapElement.first.getPosY() != pos.y))) {
          this->playerSprite->setSprite(this->playerPixel->getPixelImage(), std::vector<std::string>{std::string{this->playerPixel->getCharacter()}});
          this->playerSprite->setScale(arcade::data::Vector2f{0.04, 0.04});
          this->playerPixel->setPos(mapElement.first.getPos());
          this->playerSprite->setPosition(arcade::data::Vector2f{this->playerPixel->getPosX() * (this->playerSprite->getLocalBounds().width * this->playerSprite->getScale().x), this->playerPixel->getPosY() * (this->playerSprite->getLocalBounds().height * this->playerSprite->getScale().y)});
      }
    }
}

int arcade::pacman::Pacman::pacmanDamage(void)
{
    int exitStatus = 0;
    int nbrPacgum = 0;

    for (auto &element : this->gameStorage) {
      if (element.first.getCharacter() == 'D') {
          if ((element.first.getPosX() == this->playerPixel->getPosX()) && (element.first.getPosY() == this->playerPixel->getPosY())) {
              exitStatus = 1;
          }
      }
      if (element.first.getCharacter() == '.' || element.first.getCharacter() == 'O') {
          nbrPacgum += 1;
      }
    }
    if (nbrPacgum == 0) {
        exitStatus = 1;
    }
    return exitStatus;
}

char arcade::pacman::Pacman::getCharAtPos(arcade::data::Vector2f pos)
{
    auto it = std::find_if(this->gameStorage.begin(), this->gameStorage.end(), [&pos](std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element) {
        return (element.first.getPosX() == pos.x) && (element.first.getPosY() == pos.y);
    });
    return it != this->gameStorage.end() ? it->first.getCharacter() : '\0';
}

void arcade::pacman::Pacman::restartClock(void)
{
    this->enemiesClock = std::chrono::high_resolution_clock::now();
}

double arcade::pacman::Pacman::getTimeDelay() const
{
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(std::chrono::high_resolution_clock::now() - this->enemiesClock).count();
}

std::vector<arcade::pacman::Pixel> arcade::pacman::Pacman::createGameMap(std::string filepath)
{
    std::fstream file{filepath};
    std::string buffer;
    std::vector<std::string> map;

    if (!file) {
        std::cout << "Error: file opening" << std::endl;
        // throw
    }
    while (std::getline(file, buffer) ){
        map.push_back(buffer);
    }
    return this->createMapPixels(map);
}

std::vector<arcade::pacman::Pixel> arcade::pacman::Pacman::createMapPixels(std::vector<std::string> map)
{
    std::size_t x = 0;
    std::size_t y = 0;
    std::vector<arcade::pacman::Pixel> mapPixels;

    for (auto &line : map) {
        for (x = 0; x < line.length(); x++) {
            char actualChar = line.at(x);
            arcade::pacman::Pixel mapPixel{actualChar == ' ' ? '.' : actualChar, this->getPixelImageType(actualChar)};

            mapPixel.setPosX(static_cast<float>(x));
            mapPixel.setPosY(static_cast<float>(y));
            mapPixel.setColor(this->getPixelColorType(actualChar));
            mapPixels.push_back(mapPixel);

            std::vector<std::string> spriteCharacters;
            this->gameStorage.push_back(std::make_pair(mapPixel, std::unique_ptr<displayer::ISprite>()));
            std::unique_ptr<displayer::ISprite> &sprite = this->gameStorage.back().second;

            spriteCharacters.push_back(std::string{mapPixel.getCharacter()});
            sprite = this->graphicLib->createSprite(mapPixel.getPixelImage(), spriteCharacters, arcade::data::Vector2f{0.04, 0.04});
            sprite->setTextureRect(arcade::data::IntRect{0, 0, 500, 500});
            sprite->setColor(mapPixel.getPixelColor(), this->colorSprite(spriteCharacters.size(), spriteCharacters.at(0).length(), mapPixel.getPixelColor()));
            sprite->setPosition(arcade::data::Vector2f{mapPixel.getPosX() * (sprite->getLocalBounds().width * sprite->getScale().x), mapPixel.getPosY() * (sprite->getLocalBounds().height * sprite->getScale().y)});
        }
        y += 1;
    }
    return mapPixels;
}

std::string arcade::pacman::Pacman::getPixelImageType(char c) const
{
    if (c == '#') {
        return "ressources/pacman/wall.bmp";
    }
    if (c == 'O') {
        return "ressources/pacman/energizer.bmp";
    }
    if (c == 'P') {
        return "ressources/pacman/portal.bmp";
    }
    if (c == 'D') {
        return "ressources/pacman/ghost_r.bmp";
    }
    if (c == '-') {
        return "ressources/pacman/g_door.bmp";
    }
    return "ressources/pacman/pacgum.bmp";
}

arcade::data::Color arcade::pacman::Pacman::getPixelColorType(char c) const
{
    if (c == '#') {
        return arcade::data::Color{0, 0, 255};
    }
    if (c == 'O') {
        return arcade::data::Color{0, 255, 0};
    }
    if (c == 'P') {
        return arcade::data::Color{0, 255, 255};
    }
    if (c == 'D') {
        return arcade::data::Color{255, 0, 0};
    }
    if (c == '-') {
        return arcade::data::Color{255, 255, 255};
    }
    return arcade::data::Color{255, 255, 255};
}

std::vector<std::vector<arcade::data::Color>> arcade::pacman::Pacman::colorSprite(std::size_t i, std::size_t j, arcade::data::Color color)
{
    std::vector<std::vector<arcade::data::Color>> spriteColor;

    for (std::size_t x = 0; x < i; x++) {
        spriteColor.emplace_back(std::vector<arcade::data::Color>{});
        for (std::size_t y = 0; y < j; y++) {
            spriteColor.at(x).push_back(color);
        }
    }
    return (spriteColor);
}
