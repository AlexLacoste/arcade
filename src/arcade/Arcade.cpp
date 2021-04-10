/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include "../shared/Color.cpp"

arcade::Arcade::Arcade(const std::string &libGraphic) noexcept
{
    this->firstLib = libGraphic;
    this->highScore = 0;
    this->gameLib = nullptr;
    this->graphicLib = nullptr;
    this->dlLoaderGame = nullptr;
    this->username = "";
    // this->gameTitle = getGameTitle();
    this->state = MENU;
    this->isClosed = false;
}

arcade::Arcade::~Arcade()
{
}

void arcade::Arcade::init()
{
    std::size_t idx = 0;
    this->getLib();
    for (; idx < this->libs.size() && this->libs.at(idx).compare(this->firstLib) != 0; idx++);
    if (idx == this->libs.size())
        throw std::exception();
    this->libPositionVector = idx;
    this->dlLoaderGraphic = std::make_unique<DLLoader>(firstLib.c_str());
    this->graphicLibLoader();
}

void arcade::Arcade::run()
{
    const std::unordered_map<State, void (arcade::Arcade::*)()> mapFptr{
        {MENU, &arcade::Arcade::handleMenu}, {GAME, &arcade::Arcade::handleGame}};

    this->init();
    this->parseLibs();
    this->graphicLib->init("Arcade");
    this->initMenu();
    while (this->graphicLib->isOpen() && !this->isClosed) {
        if (this->state != CLOSED) {
            (this->*mapFptr.at(this->state))();
        }
    }
    this->graphicLib->stop();
}

void arcade::Arcade::parseLibs()
{
    // si une lib dans vecteur libs est dans game et pas dans graphical -> push dans vector libsGame
    // et delete celle dans libs si une lib dans vecteur libs est dans rien -> delete
    if (this->libs.size() == 0) {
        std::cerr << "no valid lib" << std::endl; // remove
        // throw error
    }
}

void arcade::Arcade::graphicLibLoader()
{
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>();
}

void arcade::Arcade::gameLibLoader()
{
}

void arcade::Arcade::switchNextGraphicLib()
{
    if (this->libs.size() == 1) {
        return;
    }
    this->graphicLib->stop();
    this->vectorSprite.clear();
    this->vectorText.clear();
    this->libPositionVector =
        (this->libPositionVector + 1 < this->libs.size()) ? this->libPositionVector + 1 : 0;

    this->dlLoaderGraphic =
        std::make_unique<DLLoader>(this->libs.at(this->libPositionVector).c_str());
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>();
    this->graphicLib->init("Arcade");
    this->initMenu();
}

void arcade::Arcade::switchPreviousGraphicLib()
{
    if (this->libs.size() == 1) {
        return;
    }
    this->graphicLib->stop();
    this->vectorSprite.clear();
    this->vectorText.clear();
    this->libPositionVector =
        (this->libPositionVector == 0) ? this->libs.size() - 1 : this->libPositionVector - 1;

    this->dlLoaderGraphic =
        std::make_unique<DLLoader>(this->libs.at(this->libPositionVector).c_str());
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>();
    this->graphicLib->init("Arcade");
    this->initMenu();
}

void arcade::Arcade::getLib()
{
    std::pair<std::vector<std::string>, std::vector<std::string>> pairLib = this->parseLibConf();
    for (const auto &file : std::filesystem::directory_iterator("lib")) {
        std::string tmp = file.path();
        if (this->isALib(tmp)) {
            if (std::find(pairLib.first.begin(), pairLib.first.end(), tmp) != pairLib.first.end()) {
                this->libs.push_back(tmp);
            } else if (std::find(pairLib.second.begin(), pairLib.second.end(), tmp) != pairLib.second.end()) {
                this->libsGame.push_back(tmp);
            }
        }
    }
}

void arcade::Arcade::handleGame()
{
}

void arcade::Arcade::handleGameEvent()
{
}

std::vector<std::vector<arcade::data::Color>> arcade::Arcade::colorSprite(std::size_t i, std::size_t j, arcade::data::Color color)
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

std::vector<std::string> arcade::Arcade::createSquare(std::size_t i, std::size_t j, bool isFill, char c)
{
    std::vector<std::string> square;

    for (std::size_t x = 0; x < i; x++) {
        square.emplace_back(std::string{});
        for (std::size_t y = 0; y < j; y++) {
            if (isFill) {
                square.at(x).push_back(c);
            } else if ((x == 0 || x == i - 1) || (y == 0 || y == j - 1)) {
                square.at(x).push_back(c);
            } else {
                square.at(x).push_back(' ');
            }
        }
    }
    return (square);
}

std::pair<std::vector<std::string>, std::vector<std::string>> arcade::Arcade::parseLibConf()
{
    std::pair<std::vector<std::string>, std::vector<std::string>> pairLib;
    std::ifstream fs{"lib.conf.txt"};
    std::string line{};
    int libType = 0;

    if (!fs.is_open()) {
        return (pairLib);
    }
    while (std::getline(fs, line)) {
        if (line == "graphicals:") {
            libType = 1;
        } else if (line == "games:") {
            libType = 2;
        } else if (line[0] == '-' && isALib(line.substr(1))) {
            line = line.substr(line.find("lib/arcade_"));
            if (libType == 1) {
                pairLib.first.emplace_back(line);
            }
            else if (libType == 2) {
                pairLib.second.emplace_back(line);
            }
        }
    }
    fs.close();
    return (pairLib);
}

bool arcade::Arcade::isALib(const std::string &libPath)
{
    std::stringstream ss{libPath};
    std::string path{};

    ss >> path;
    if (!ss.eof())
        return (false);
    if (path.find("lib/arcade_") == 0 && path.find_last_of(".so") == path.size() - 1) {
        return (true);
    }
    return (false);
}
