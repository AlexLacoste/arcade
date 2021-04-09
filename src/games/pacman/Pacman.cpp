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
}
void arcade::pacman::Pacman::update()

{
}

void arcade::pacman::Pacman::stop()
{
}

std::vector<arcade::pacman::Pixel> arcade::pacman::Pacman::createGameMap(std::string filepath) const
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

std::vector<arcade::pacman::Pixel> arcade::pacman::Pacman::createMapPixels(std::vector<std::string> map) const
{
    int y = 0;
    std::vector<arcade::pacman::Pixel> mapPixels;

    std::for_each(map.begin(), map.end(), [&](std::string line) {
        for (std::size_t index = 0; index < line.length(); ++index) {
            arcade::pacman::Pixel mapPixel{line.at(index), static_cast<float>(index), static_cast<float>(y)};

            mapPixels.push_back(mapPixel);
        }
        y += 1;
    });
    /*std::for_each(mapPixels.begin(), mapPixels.end(), [](arcade::pacman::Pixel pixel) {
        std::cout << "Char: " << pixel.getCharacter() << " at pos : [" << pixel.getPosX()  << ", " << pixel.getPosY() << "]" << std::endl;
    });*/
}
