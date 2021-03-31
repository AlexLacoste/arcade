/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Arcade
*/

#include <dirent.h>
#include <string>
#include <vector>
#include "DLLoader/DLLoader.hpp"
#include "Arcade.hpp"

arcade::Arcade::Arcade(const std::string &libGraphic)
{
    this->highScore = 0;
    this->libs = this->getLib();
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
    const std::array<function> fptr = [];
    std::size_t state = 0;

    while (this->graphicLib->isOpen()) {
        this->(*fptr.at(state))();
        this->graphicLib->display();
    }
}

void arcade::Arcade::graphicLibLoader(const std::string &path)
{
    this->graphicLib = this->dlLoaderGraphic->getInstance<IDisplayModule>("IDisplayModule");
}

std::vector<std::string> arcade::Arcade::getLib()
{
    std::vector<std::string> libs;
    struct dirent *read_dir = nullptr;
    DIR *dir = opendir("lib");
    std::string lib;

    if (!dir)
        throw exception;
    read_dir = readdir(dir);
    for (; read_dir; read_dir = readdir(dir)) {
        lib = read_dir->d_name;
        if (lib[0] != '.' && lib.length() > 3 && lib[lib.length() - 3] == '.'
            && lib[lib.length() - 2] == 's' && lib[lib.length() - 1] == 'o') {
            libs.push_back(lib);
        }
    }
    closedir(dir);
    return libs;
}