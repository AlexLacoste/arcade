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
#include <algorithm>
#include <memory>
#include <fstream>

#include "IGame.hpp"

namespace arcade
{
    namespace pacman
    {
        class Pixel {
            public:
                Pixel(char c, float x, float y) : character(c), x(x), y(y) {};
                ~Pixel() {};

            char getCharacter(void) const { return this->character; };
            float getPosX(void) const { return this->x; };
            float getPosY(void) const { return this->y; };

            protected:
            private:
                char character;
                float x;
                float y;
        };

        class Pacman : public arcade::IGame {
            public:
                Pacman();
                ~Pacman();

                void init(std::shared_ptr<displayer::IDisplay> &disp) override;
                void update() override;
                void stop() override;

            protected:
            private:
                std::vector<Pixel> createGameMap(std::string filepath) const;
                std::vector<Pixel> createMapPixels(std::vector<std::string> map) const;

                std::shared_ptr<displayer::IDisplay> graphicLib;
                std::vector<Pixel> gameMap;
        };
    }
}

#endif /* !PACMAN_HPP_ */