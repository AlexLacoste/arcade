/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#include "Pacman.hpp"

extern "C" std::unique_ptr<arcade::IGame> entry_point()
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
}
void arcade::pacman::Pacman::update()
{
    std::for_each(this->gameSprites.begin(), this->gameSprites.end(), [&](std::unique_ptr<displayer::ISprite> &sprite) {
        this->graphicLib->draw(sprite);
    });
}

void arcade::pacman::Pacman::stop()
{
}

void arcade::pacman::Pacman::createAllSprites(void)
{
    float offsetX = 0;
    float offsetY = 0;

    std::for_each(this->gameMap.begin(), this->gameMap.end(), [&](arcade::pacman::Pixel pixel) {
      std::vector<std::string> spriteCharacters;
      std::unique_ptr<displayer::ISprite> sprite;

      spriteCharacters.push_back(std::string{pixel.getCharacter()});
      sprite = this->graphicLib->createSprite(pixel.getPixelImage(), spriteCharacters, arcade::data::Vector2f{0.04, 0.04});
      sprite->setTextureRect(arcade::data::IntRect{0, 0, 500, 500});
      sprite->setColor(pixel.getPixelColor(), this->colorSprite(spriteCharacters.size(), spriteCharacters.at(0).length(), pixel.getPixelColor()));
      sprite->setPosition(arcade::data::Vector2f{pixel.getPosX() + offsetX, pixel.getPosY() + offsetY});
      this->gameSprites.push_back(std::move(sprite));
      offsetX += 20;
      if ((pixel.getPosX() + 1) >= this->mapWidth) {
          offsetX = 0;
          offsetY += 20;
      }
    });
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
            arcade::pacman::Pixel mapPixel{actualChar, this->getPixelImageType(actualChar)};

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
        return "ressources/pacman/wall.png";
    }
    if (c == 'O') {
        return "ressources/pacman/energizer.png";
    }
    if (c == 'P') {
        return "ressources/pacman/wall.png";
    }
    return "ressources/pacman/pacgum.png";
}

arcade::data::Color arcade::pacman::Pacman::getPixelColorType(char c) const
{
    if (c == '#') {
        return arcade::data::Color{0, 165, 255};
    }
    if (c == 'O') {
        return arcade::data::Color{255, 141, 50};
    }
    if (c == 'P') {
        return arcade::data::Color{0, 165, 255};
    }
    return arcade::data::Color{246, 141, 67};
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
