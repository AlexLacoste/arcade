/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#include "Pacman.hpp"

extern "C" std::unique_ptr<arcade::games::IGame> GAMES_ENTRY_POINT()
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
    this->graphicLib = disp;
    this->gameMap = this->createGameMap("ressources/pacman/pacman_map.txt");
    this->createAllSprites();
    this->createPlayer();
}
arcade::games::GameStatus arcade::pacman::Pacman::update()
{
    std::for_each(this->gameSprites.begin(), this->gameSprites.end(), [&](std::unique_ptr<displayer::ISprite> &sprite) {
        this->graphicLib->draw(sprite);
    });
    this->graphicLib->draw(playerSprite);
    this->handleEvents();
    return arcade::games::PLAYING;
}

void arcade::pacman::Pacman::stop()
{
}

void arcade::pacman::Pacman::restart()
{
}

unsigned int arcade::pacman::Pacman::getScore() const
{
    return 0;
}

void arcade::pacman::Pacman::createPlayer(void)
{
    arcade::data::Vector2f position{13, 23};

    /* CREATE PLAYER PIXEL */
    arcade::pacman::Pixel pixel{'G', "ressources/pacman/pacman_l.bmp", position.x, position.y};

    pixel.setColor(arcade::data::Color{255, 255, 0});
    this->playerPixel = std::make_unique<Pixel>(pixel);

    /* CREATE PLAYER SPRITE */
    std::unique_ptr<displayer::ISprite> sprite;

    sprite = this->graphicLib->createSprite(this->playerPixel->getPixelImage(), std::vector<std::string>{std::string{this->playerPixel->getCharacter()}}, arcade::data::Vector2f{0.04, 0.04});
    sprite->setTextureRect(arcade::data::IntRect{0, 0, 500, 500});
    sprite->setColor(this->playerPixel->getPixelColor(), this->colorSprite(1, 1, this->playerPixel->getPixelColor()));
    sprite->setPosition(arcade::data::Vector2f{position.x * (sprite->getTextureRect().width * sprite->getScale().x), position.y * (sprite->getTextureRect().height * sprite->getScale().y)});
    this->playerSprite = std::move(sprite);
}

void arcade::pacman::Pacman::createAllSprites(void)
{
    std::for_each(this->gameMap.begin(), this->gameMap.end(), [&](arcade::pacman::Pixel pixel) {
      std::vector<std::string> spriteCharacters;
      std::unique_ptr<displayer::ISprite> sprite;

      spriteCharacters.push_back(std::string{pixel.getCharacter()});
      sprite = this->graphicLib->createSprite(pixel.getPixelImage(), spriteCharacters, arcade::data::Vector2f{0.04, 0.04});
      sprite->setTextureRect(arcade::data::IntRect{0, 0, 500, 500});
      sprite->setColor(pixel.getPixelColor(), this->colorSprite(spriteCharacters.size(), spriteCharacters.at(0).length(), pixel.getPixelColor()));
      sprite->setPosition(arcade::data::Vector2f{pixel.getPosX() * (sprite->getTextureRect().width * sprite->getScale().x), pixel.getPosY() * (sprite->getTextureRect().height * sprite->getScale().y)});
      this->gameSprites.push_back(std::move(sprite));
    });
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

void arcade::pacman::Pacman::movePlayer(std::string imagePath, arcade::data::Vector2i movement)
{
    float diffX = this->playerPixel->getPosX()  + (movement.x);
    float diffY = this->playerPixel->getPosY()  + (movement.y);

    this->playerPixel->setPixelImage(imagePath);
    this->playerSprite->setSprite(this->playerPixel->getPixelImage(), std::vector<std::string>{std::string{this->playerPixel->getCharacter()}});
    this->playerSprite->setScale(arcade::data::Vector2f{0.04, 0.04});
    this->playerSprite->setPosition(arcade::data::Vector2f{this->playerPixel->getPosX() * (this->playerSprite->getTextureRect().width * this->playerSprite->getScale().x), this->playerPixel->getPosY() * (this->playerSprite->getTextureRect().height * this->playerSprite->getScale().y)});
    if (this->getCharAtPos(arcade::data::Vector2f{diffX, diffY}) != '#') {
        this->playerPixel->setPosX(diffX);
        this->playerPixel->setPosY(diffY);
        this->playerSprite->move((this->playerSprite->getTextureRect().width * this->playerSprite->getScale().x) * (movement.x), (this->playerSprite->getTextureRect().height * this->playerSprite->getScale().y) * (movement.y));
    }
}

char arcade::pacman::Pacman::getCharAtPos(arcade::data::Vector2f pos) const
{
    char result = '\0';

    std::for_each(this->gameMap.begin(), this->gameMap.end(), [&result, &pos](arcade::pacman::Pixel pixel) {
        if ((pixel.getPosX() == pos.x) && (pixel.getPosY() == pos.y)) {
            result = pixel.getCharacter();
        }
    });
    return result;
}

std::vector<arcade::pacman::Pixel> arcade::pacman::Pacman::createGameMap(std::string filepath)
{
    std::fstream file{filepath};
    std::string buffer;
    std::vector<std::string> map;

    if (!file) {
        std::cout << "Error: file opening" << std::endl;
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

    std::for_each(map.begin(), map.end(), [&](std::string line) {
        for (x = 0; x < line.length(); x++) {
            char actualChar = line.at(x);
            arcade::pacman::Pixel mapPixel{actualChar == ' ' ? '.' : actualChar, this->getPixelImageType(actualChar)};

            mapPixel.setPosX(static_cast<float>(x));
            mapPixel.setPosY(static_cast<float>(y));
            mapPixel.setColor(this->getPixelColorType(actualChar));
            mapPixels.push_back(mapPixel);
        }
        y += 1;
    });
    this->mapWidth = x;
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
        return "ressources/pacman/wall.bmp";
    }
    return "ressources/pacman/pacgum.bmp";
}

arcade::data::Color arcade::pacman::Pacman::getPixelColorType(char c) const
{
    if (c == '#') {
        return arcade::data::Color{0, 0, 255};
    }
    if (c == 'O') {
        return arcade::data::Color{255, 0, 0};
    }
    if (c == 'P') {
        return arcade::data::Color{0, 255, 255};
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
