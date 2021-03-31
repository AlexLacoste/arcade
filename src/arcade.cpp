/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Arcade
*/

// #include <dirent.h>
#include <filesystem>
#include <string>
#include <vector>
#include "DLLoader/DLLoader.hpp"
#include "Arcade.hpp"

arcade::Arcade::Arcade(const std::string &libGraphic)
{
    this->highScore = 0;
    this->getLib();
    for (std::size_t i; i < this->libs.size() && this->libs.at(i).compare(libGraphic) != 0; i++)
        this->libPositionVector = i;
    this->gameLib = nullptr;
    this->graphicLib = nullptr;
    this->dlLoaderGame = nullptr;
    this->dlLoaderGraphic = std::make_unique<DLLoader>(libGraphic.c_str());
    this->graphicLibLoader(libGraphic);
    this->username = "";
    this->gameTitle = getGameTitle();
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::run()
{
    const std::array<function> fptr = []; // faire unurder_map
    std::size_t state = 0; // enum

    while (this->graphicLib->isOpen()) {
        this->(*fptr.at(state))();
        this->graphicLib->display();
    }
}

void arcade::Arcade::graphicLibLoader(const std::string &path)
{
    this->graphicLib = this->dlLoaderGraphic->getInstance<IDisplayModule>();
}

void arcade::Arcade::getLib()
{
    for (const auto &file : std::filesystem::directory_iterator("lib")) {
        std::string tmp = file.path();
        if (tmp.find_last_of(".so"))
            this->libs.push_back(tmp);
    }
}