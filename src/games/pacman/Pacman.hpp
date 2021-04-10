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
                Pixel(char c, std::string pixelImage, float x = 0.0, float y = 0.0) : character(c), pixelImage(pixelImage), x(x), y(y) {};
                ~Pixel() {};

                char getCharacter(void) const { return this->character; };
                std::string getPixelImage(void) const { return this->pixelImage; };
                float getPosX(void) const { return this->x; };
                float getPosY(void) const { return this->y; };
                arcade::data::Color getPixelColor(void) const { return this->color; };

                void setPosX(float x) { this->x = x; };
                void setPosY(float y) { this->y = y; };
                void setColor(arcade::data::Color color) { this->color = color; };

            protected:
            private:
                char character;
                std::string pixelImage;
                arcade::data::Color color;
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
                void createAllSprites(void);

                std::vector<Pixel> createGameMap(std::string filepath) const;
                std::vector<Pixel> createMapPixels(std::vector<std::string> map) const;
                std::string getPixelImageType(char c) const;
                arcade::data::Color getPixelColorType(char c) const;

                std::vector<std::vector<arcade::data::Color>> colorSprite(std::size_t i, std::size_t j, arcade::data::Color color);

                std::shared_ptr<displayer::IDisplay> graphicLib;
                std::vector<Pixel> gameMap;
                std::vector<std::unique_ptr<displayer::ISprite>> gameSprites;
        };
    }
}

#endif /* !PACMAN_HPP_ */