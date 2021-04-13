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
#include "../games/IGame.hpp"
#include "../shared/IDisplayModule.hpp"
#include "DLLoader/DLLoader.hpp"

namespace arcade
{
    class Arcade {
      public:
        enum State {
          MENU,
          GAME,
          CLOSED,
        };

        Arcade(const std::string &libGraphic) noexcept;
        ~Arcade();

        void run();
      private:
        void init();
        void graphicLibLoader(std::string lib);
        void gameLibLoader();
        void switchNextGraphicLib();
        void switchPreviousGraphicLib();
        void switchSpecificGraphicLib();
        void switchNextGameLib();
        void switchPreviousGameLib();
        void getLib();
        std::vector<std::string> libs;
        std::vector<std::string> libsGame;
        std::size_t libPositionVector;

        bool isChooseGame;
        std::size_t posChooseGraphic;
        std::size_t posChooseGame;

        std::string firstLib;

        // std::size_t &getHighScore() const;
        std::size_t highScore;

        std::unique_ptr<IGame> gameLib;
        std::shared_ptr<displayer::IDisplay> graphicLib;

        std::unique_ptr<DLLoader> dlLoaderGraphic;
        std::unique_ptr<DLLoader> dlLoaderGame;

        std::string username;
    
        // std::vector<std::string> getGameTitle();
        std::vector<std::string> gamesTitle;

        // std::unordered_map<std::string, std::size_t> getGameHighScore();
        std::unordered_map<std::string, std::size_t> gameHighScore;

        bool isClosed;

        State state;

        void handleMenu();
        void handleEvents();

        void handleGame();
        void handleGameEvent();

        void initMenu();
        void initTextMenu();
        void initTextLib();
        void initSpriteMenu();

        std::vector<std::unique_ptr<arcade::displayer::IText>> vectorTextInit;
        std::vector<std::unique_ptr<arcade::displayer::IText>> vectorTextGame;
        std::vector<std::unique_ptr<arcade::displayer::IText>> vectorTextLib;
        std::vector<std::unique_ptr<arcade::displayer::IText>> vectorTextScore;
        std::unique_ptr<arcade::displayer::IText> iTextUsername;
        std::vector<std::unique_ptr<arcade::displayer::ISprite>> vectorSprite;

        void clearVector();

        std::vector<std::vector<arcade::data::Color>> colorSprite(std::size_t i, std::size_t j, arcade::data::Color color);
        std::vector<std::string> createSquare(std::size_t i, std::size_t j, bool isFill, char c);

        std::pair<std::vector<std::string>, std::vector<std::string>> parseLibConf();
        bool isALib(const std::string &libPath);

    };
} // namespace arcade

#endif /* !ARCADE_HPP_ */