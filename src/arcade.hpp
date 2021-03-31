/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** arcade
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "games/IGame.hpp"
#include "graphics/IDisplayModule.hpp"
#include "DLLoader/DLLoader.hpp"

namespace arcade
{
    class Arcade {
      public:
        Arcade(const std::string &libGraphic);
        ~Arcade();

        void run();
      private:
        void graphicLibLoader(const std::string &path);
        void gameLibLoader(const std::string &path);
        void switchGraphicLib(const std::string &path);
        std::vector<std::string> getLib();
        std::vector<std::string> libs;

        std::size_t &getHighScore() const;
        std::size_t highScore;

        std::size_t libPositionVector;
        std::unique_ptr<IGame> gameLib;
        std::unique_ptr<IDisplayModule> graphicLib;

        std::unique_ptr<DLLoader> dlLoaderGraphic;
        std::unique_ptr<DLLoader> dlLoaderGame;

        void chooseUsername();
        std::string username;
    
        std::vector<std::string> getGameTitle();
        std::vector<std::string> gameTitle;

        std::unordered_map<std::string, std::size_t> getGameHighScore(std::string username, std::string game);
        std::unordered_map<std::string, std::size_t> gameHighScore;
    };
} // namespace arcade

#endif /* !ARCADE_HPP_ */