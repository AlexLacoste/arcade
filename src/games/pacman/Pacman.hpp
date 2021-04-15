/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>

#include "../../shared/IGame.hpp"

namespace arcade
{
    namespace pacman
    {
        class Pixel {
            public:
                Pixel(char c, std::string pixelImage, float x = 0.0, float y = 0.0) : character(c), pixelImage(pixelImage), x(x), y(y), isInMaze(false) {};
                ~Pixel() {};

                char getCharacter(void) const { return this->character; };
                std::string getPixelImage(void) const { return this->pixelImage; };
                float getPosX(void) const { return this->x; };
                float getPosY(void) const { return this->y; };
                data::Vector2f getPos(void) const { return data::Vector2f{this->x, this->y}; };
                arcade::data::Color getPixelColor(void) const { return this->color; };
                bool getIsInMaze(void) { return this->isInMaze; };

                void setPosX(float x) { this->x = x; };
                void setPosY(float y) { this->y = y; };
                void setPos(data::Vector2f pos) { this->x = pos.x; this->y = pos.y; };
                void setColor(arcade::data::Color color) { this->color = color; };
                void setPixelImage(std::string pixelImage) { this->pixelImage = pixelImage; };
                void setIsInMaze(bool statement) { this->isInMaze = statement; };

            protected:
            private:
                char character;
                std::string pixelImage;
                arcade::data::Color color;
                float x;
                float y;
                bool isInMaze;
        };

        class Pacman : public arcade::games::IGame {
            public:
                Pacman();
                ~Pacman();

                void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) override;
                arcade::games::GameStatus update() override;
                void stop() override;
                void restart() override;
                unsigned int getScore() const override;

            protected:
            private:
                void createPlayer(void);
                void createTexts(void);

                void handleEvents(void);
                void updateTexts(void);
                void moveEnemies(void);
                void moveOneEnemie(std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &enemie, arcade::data::Vector2i infoEnemie, std::string imagePath, arcade::data::Vector2i movement);
                void checkPreviousEnemiesMove(arcade::data::Vector2i infoEnemie);
                void movePlayer(std::string imagePath, data::Vector2i movement);
                void eatPacgums(void);
                void onTeleportPointEnemie(std::pair<Pixel, std::unique_ptr<displayer::ISprite>> &element, data::Vector2f pos);
                void onTeleportPointPlayer(data::Vector2f pos);
                int pacmanDamage(void);

                char getCharAtPos(data::Vector2f pos);
                void restartClock(void);
                double getTimeDelay(void) const;

                std::vector<Pixel> createGameMap(std::string filepath);
                std::vector<Pixel> createMapPixels(std::vector<std::string> map);
                std::string getPixelImageType(char c) const;
                arcade::data::Color getPixelColorType(char c) const;
                std::vector<std::vector<arcade::data::Color>> colorSprite(std::size_t i, std::size_t j, arcade::data::Color color);

                std::shared_ptr<displayer::IDisplay> graphicLib;
                std::vector<Pixel> gameMap;
                std::vector<std::pair<Pixel, std::unique_ptr<displayer::ISprite>>> gameStorage;
                std::unique_ptr<Pixel> playerPixel;
                std::unique_ptr<displayer::ISprite> playerSprite;
                std::size_t playerScore;
                std::vector<std::unique_ptr<displayer::IText>> gameTexts;
                std::chrono::time_point<std::chrono::high_resolution_clock> enemiesClock;
                std::vector<int> previousEnemiesMove;
        };
    }
}

#endif /* !PACMAN_HPP_ */