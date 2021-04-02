/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Arcade
*/

#include <filesystem>
#include <string>
#include <vector>
#include <iostream>
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
    this->graphicLibLoader();
    this->username = "";
    // this->gameTitle = getGameTitle();
    this->state = USERNAME;
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::run()
{
    // const std::unordered_map<function> fptr = [];
    std::unique_ptr<displayer::IText> textLib;

    this->graphicLib->init();
    textLib = this->graphicLib->createText("Merci Jacquie et Honoré");
    while (this->graphicLib->isOpen()) {
        // this->(*fptr.at(state))();
        this->graphicLib->clearWindow();
        this->graphicLib->draw(textLib);
        this->graphicLib->display();
    }
}

void arcade::Arcade::graphicLibLoader()
{
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplayModule>();
}

void arcade::Arcade::gameLibLoader(const std::string &path)
{}

void arcade::Arcade::switchGraphicLib(const std::string &path)
{}

void arcade::Arcade::getLib()
{
    for (const auto &file : std::filesystem::directory_iterator("lib")) {
        std::string tmp = file.path();
        if (tmp.find_last_of(".so"))
            this->libs.push_back(tmp);
    }
}
