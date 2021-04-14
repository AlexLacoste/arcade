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
    this->libPositionVector = 0;
    this->gameLib = nullptr;
    this->graphicLib = nullptr;
    this->dlLoaderGame = nullptr;
    this->username = "user____";
    this->realUsername = "user";
    this->isChooseGame = true;
    this->posChooseGraphic = 0;
    this->posChooseGame = 0;
    this->state = MENU;
    this->isClosed = false;
}

arcade::Arcade::~Arcade()
{
    if (this->graphicLib) {
        this->graphicLib->stop();
    }
}

void arcade::Arcade::init()
{
    std::size_t idx = 0;
    this->getLib();
    for (; idx < this->libs.size(); idx++) {
        if (std::filesystem::equivalent(this->firstLib, this->libs.at(idx))) {
            break;
        }
    }
    if (idx == this->libs.size())
        throw std::exception();
    if (this->libs.size() == 0 || this->libsGame.size() == 0) {
        // throw error
    }
    this->libPositionVector = idx;
    this->graphicLibLoader(this->firstLib);
    this->parseHighscore();
    this->verifHighscore();
}

void arcade::Arcade::run()
{
    const std::unordered_map<State, void (arcade::Arcade::*)()> mapFptr{
        {MENU, &arcade::Arcade::handleMenu}, {GAME, &arcade::Arcade::handleGame}};

    this->init();
    this->graphicLib->init("Arcade");
    this->initMenu();
    while (this->graphicLib->isOpen() && !this->isClosed) {
        this->handleEvents();
        this->graphicLib->clearWindow();
        if (this->state != CLOSED) {
            (this->*mapFptr.at(this->state))();
        }
        this->graphicLib->display();
    }
    this->graphicLib->stop();
    this->generateHighscoreFile();
}

void arcade::Arcade::graphicLibLoader(std::string lib)
{
    this->dlLoaderGraphic = std::make_unique<DLLoader>(lib.c_str());
    this->graphicLib = this->dlLoaderGraphic->getInstance<displayer::IDisplay>();
}

void arcade::Arcade::gameLibLoader()
{
    this->dlLoaderGame = std::make_unique<DLLoader>(this->libsGame.at(this->posChooseGame));
    this->gameLib = this->dlLoaderGame->getInstance<arcade::games::IGame>();
    this->gameLib->init(this->graphicLib);
}

void arcade::Arcade::clearVector()
{
    this->vectorSprite.clear();
    this->vectorTextInit.clear();
    this->vectorTextLib.clear();
    this->vectorTextGame.clear();
}

void arcade::Arcade::switchNextGraphicLib()
{
    if (this->libs.size() == 1) {
        return;
    }
    this->graphicLib->stop();
    this->libPositionVector = (this->libPositionVector + 1 < this->libs.size()) ? this->libPositionVector + 1 : 0;
    this->clearVector();
    this->graphicLibLoader(this->libs.at(this->libPositionVector));
    this->graphicLib->init("Arcade");
    this->initMenu();
}

void arcade::Arcade::switchPreviousGraphicLib()
{
    if (this->libs.size() == 1) {
        return;
    }
    this->graphicLib->stop();
    this->libPositionVector = (this->libPositionVector == 0) ? this->libs.size() - 1 : this->libPositionVector - 1;
    this->clearVector();
    this->graphicLibLoader(this->libs.at(this->libPositionVector));
    this->graphicLib->init("Arcade");
    this->initMenu();
}

void arcade::Arcade::switchSpecificGraphicLib()
{
    if (this->libs.size() == 1) {
        return;
    }
    this->graphicLib->stop();
    this->clearVector();
    this->graphicLibLoader(this->libs.at(this->posChooseGraphic));
    this->graphicLib->init("Arcade");
    this->initMenu();
}

void arcade::Arcade::switchPreviousGameLib()
{
    if (this->libsGame.size() == 1) {
        return;
    }
    this->gameLib->stop();
    this->posChooseGame = (this->posChooseGame == 0) ? this->libsGame.size() - 1 : this->posChooseGame - 1;
    this->gameLibLoader();
}

void arcade::Arcade::switchNextGameLib()
{
    if (this->libsGame.size() == 1) {
        return;
    }
    this->gameLib->stop();
    this->posChooseGame = (this->posChooseGame + 1 < this->libsGame.size()) ? this->posChooseGame + 1 : 0;
    this->gameLibLoader();
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
    this->gameLib->update();
}

std::vector<std::vector<arcade::data::Color>> arcade::Arcade::colorSprite(
    std::size_t i, std::size_t j, arcade::data::Color color)
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
            } else if (libType == 2) {
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

void arcade::Arcade::handleEvents()
{
    std::vector<arcade::data::Event> events = this->graphicLib->getEvents();

    for (auto event : events) {
        if (event.type == arcade::data::WINDOW_CLOSED) {
            this->isClosed = true;
            return;
        }
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            switch (event.key) {
                case ('.'):
                    this->switchPreviousGraphicLib();
                    if (this->state == GAME) {
                        this->gameLib->stop();
                        this->gameLib->init(this->graphicLib);
                    }
                    return;
                case ('/'):
                    this->switchNextGraphicLib();
                    if (this->state == GAME) {
                        this->gameLib->stop();
                        this->gameLib->init(this->graphicLib);
                    }
                    return;
            }
            if (this->state == MENU) {
                if (event.key >= 'a' && event.key <= 'z' || event.key >= 'A' && event.key <= 'Z') {
                    this->addCharToUsername(event.key);
                    return;
                }
                if (event.key == 127) {
                    this->deleteOneCharUsername();
                    return;
                }
                switch (static_cast<int>(event.keyCode)) {
                    case (arcade::data::UP):
                        if (this->isChooseGame) {
                            this->posChooseGame =
                                (this->posChooseGame == 0) ? this->libsGame.size() - 1 : this->posChooseGame - 1;
                        } else {
                            this->posChooseGraphic =
                                (this->posChooseGraphic == 0) ? this->libs.size() - 1 : this->posChooseGraphic - 1;
                        }
                        break;
                    case (arcade::data::DOWN):
                        if (this->isChooseGame) {
                            this->posChooseGame =
                                (this->posChooseGame + 1 < this->libsGame.size()) ? this->posChooseGame + 1 : 0;
                        } else {
                            this->posChooseGraphic =
                                (this->posChooseGraphic + 1 < this->libs.size()) ? this->posChooseGraphic + 1 : 0;
                        }
                        break;
                    case (arcade::data::LEFT):
                        this->isChooseGame = !this->isChooseGame;
                        if (this->isChooseGame) {
                            this->posChooseGame = 0;
                        } else {
                            this->posChooseGraphic = 0;
                        }
                        break;
                    case (arcade::data::RIGHT):
                        this->isChooseGame = !this->isChooseGame;
                        if (this->isChooseGame) {
                            this->posChooseGame = 0;
                        } else {
                            this->posChooseGraphic = 0;
                        }
                        break;
                    case (arcade::data::ESCAPE):
                        this->state = CLOSED;
                        this->isClosed = true;
                        return;
                    case (arcade::data::ENTER):
                        if (this->isChooseGame) {
                            if (this->realUsername.size() != 0) {
                                this->gameLibLoader();
                                this->state = GAME;
                            }
                        } else {
                            this->switchSpecificGraphicLib();
                        }
                        return;
                    case (arcade::data::BACKSPACE):
                        this->deleteOneCharUsername();
                        break;
                }
            } else if (this->state == GAME) {
                switch (event.key) {
                    case ('w'):
                        this->switchPreviousGameLib();
                        return;
                    case ('x'):
                        this->switchNextGameLib();
                        return;
                    case ('r'):
                        this->gameLib->restart();
                        return;
                    case ('m'):
                        this->state = MENU;
                        this->gameLib->stop();
                        this->clearVector();
                        this->initMenu();
                        return;
                }
                switch (static_cast<int>(event.keyCode)) {
                    case (arcade::data::ESCAPE):
                        this->gameLib->stop();
                        this->isClosed = true;
                        this->state = CLOSED;
                        return;
                }
            }
        }
    }
}

void arcade::Arcade::parseHighscore()
{
    std::ifstream fs{"highscore.txt"};
    std::string line{};

    if (!fs.is_open()) {
        return;
    }
    while (std::getline(fs, line)) {
        if (line.find_last_of(':') == line.size() - 1) {
            line = line.substr(0, line.size() - 1);
            if (std::find(this->libsGame.begin(), this->libsGame.end(), line) != this->libsGame.end()) {
                this->getHighscore(fs, line);
            }
        }
    }
    fs.close();
}

void arcade::Arcade::getHighscore(std::ifstream &fs, const std::string &game)
{
    std::vector<std::pair<std::string, std::size_t>> gameHighscore{};
    std::string line{};
    std::stringstream ss{};
    std::size_t i = 0;

    for (; i < 3 && std::getline(fs, line); i++) {
        if (line[0] != '-')
            break;
        std::pair<std::string, std::size_t> highscore;
        ss.str(line.substr(1));
        ss >> highscore.first >> highscore.second;
        std::cout << highscore.first << ' ' << highscore.second << std::endl;
        if (highscore.first.empty() || highscore.second == 0)
            return;
        if (ss.eof())
            gameHighscore.emplace_back(highscore);
        ss.clear();
    }
    if (gameHighscore.size() != 3)
        return;
    std::cout << "Highscore find for : " << game << std::endl;
    this->sortHighscore(gameHighscore);
    this->highscoreMap[game] = gameHighscore;
}

void arcade::Arcade::generateHighscore(const std::string &game)
{
    std::vector<std::pair<std::string, std::size_t>> gameHighscore{};

    if (std::find(this->libsGame.begin(), this->libsGame.end(), game) != this->libsGame.end()) {
        gameHighscore.emplace_back(std::pair<std::string, std::size_t>{"Jay", 10000});
        gameHighscore.emplace_back(std::pair<std::string, std::size_t>{"Jay", 5000});
        gameHighscore.emplace_back(std::pair<std::string, std::size_t>{"Jay", 2000});
        this->highscoreMap[game] = gameHighscore;
    }
}

void arcade::Arcade::verifHighscore()
{
    for (const auto &game : this->libsGame) {
        if (this->highscoreMap.count(game) == 0) {
            std::cout << "No highscore : " << game << std::endl;
            generateHighscore(game);
        }
    }
}

void arcade::Arcade::generateHighscoreFile()
{
    std::ofstream fs{"highscore.txt"};

    if (!fs.is_open()) {
        return;
    }
    for (const auto &game : this->libsGame) {
        if (this->highscoreMap.count(game)) {
            this->sortHighscore(highscoreMap[game]);
            fs << game << ':' << std::endl;
            for (const auto &pair : this->highscoreMap[game]) {
                fs << "- " << pair.first << ' ' << pair.second << std::endl;
            }
        }
    }
}

void arcade::Arcade::sortHighscore(std::vector<std::pair<std::string, std::size_t>> &highscore)
{
    for (std::size_t i = highscore.size() - 2; i > 0; i--) {
        for (std::size_t j = 0; j <= i; j++) {
            if (highscore.at(j).second < highscore.at(j + 1).second)
                highscore.at(j).swap(highscore.at(j + 1));
        }
    }
    while (highscore.size() > 3) {
        highscore.pop_back();
    }
}

void arcade::Arcade::addHighscore(const std::string &game, const std::string &user, size_t score)
{
    if (this->highscoreMap.count(game)) {
        this->highscoreMap[game].emplace_back(std::pair<std::string, std::size_t>{user, score});
        sortHighscore(this->highscoreMap[game]);
    }
}