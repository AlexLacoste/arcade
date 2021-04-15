/*
** EPITECH PROJECT, 2020
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Nibbler.hpp
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../shared/IGame.hpp"

namespace arcade
{
    namespace nibbler
    {
        class Cell
        {
            public:
                Cell(char c, const std::string &image, int posX = 0, int posY = 0) : character(c), imagePath(image), pos(posX, posY) {};
                Cell(char c, const std::string &image, const data::Vector2i &vector) : character(c), imagePath(image), pos(vector) {};
                ~Cell() {};

                char getCharacter() const {return this->character;};
                void setCharacter(char c) {this->character = c;};
                std::string getImagePath() const {return this->imagePath;};
                data::Vector2i getPos() const {return this->pos;};
                int getPosX() const {return this->pos.x;};
                int getPosY() const {return this->pos.y;};
                void setColor(arcade::data::Color color) {this->color = color;};
                arcade::data::Color getColor() const {return this->color;};
                void setImagePath(const std::string &image) {this->imagePath = image;};


            private:
                char character;
                std::string imagePath;
                data::Color color;
                data::Vector2i pos;
        };
        class Player
        {
            public:
                enum Direction
                {
                    UP, DOWN, LEFT, RIGHT,
                };
                Player();
                ~Player();

                void initPlayer(const std::vector<std::string> &map);
                Direction getDirection() const;
                void setDirection(Direction direct);
                const std::vector<Cell> &getPlayer() const;
                const std::vector<displayer::ISprite> &getSpite() const;
                bool move(std::vector<std::vector<Cell>> &cellMap, double lastFrame);
                void emptySprite();
                void restart();
                data::Vector2i getVectorMove(Direction direction) const;
                void upSize(size_t size);

            private:
                std::vector<Cell> snakeBody;
                std::vector<std::unique_ptr<displayer::ISprite>> snakeSprite;
                Direction direction;
                Direction newDirection;
                float timeSinceLastMove;
                size_t size;
        };

        class Nibbler : public arcade::games::IGame
        {
            public:
                Nibbler();
                ~Nibbler();

                void init(std::shared_ptr<arcade::displayer::IDisplay> &disp) override;
                arcade::games::GameStatus update() override;
                void stop() override;
                void restart() override;
                unsigned int getScore() const override;
            
            private:
                void handleEvents(void);
                void getMap(const std::string &mapPath);
                void initMap();
                void initSpriteVector();
                void drawGame();
                void initText();
                std::string createTextNumber(const std::string &text, unsigned int score);
                std::vector<std::vector<arcade::data::Color>> colorSprite(std::size_t i, std::size_t j, arcade::data::Color color);
                
                std::shared_ptr<displayer::IDisplay> graphicLib;
                std::vector<std::string> gameMap;
                std::vector<std::vector<Cell>> cellMap;
                std::vector<std::unique_ptr<displayer::ISprite>> spriteMap;
                std::vector<displayer::ISprite> foodMap;
                Player player;
                double time;
                size_t duration;
                std::size_t score;
                std::unique_ptr<displayer::IText> highscoreText;
                std::unique_ptr<displayer::IText> timeText;
                std::unique_ptr<displayer::IText> messageText;
                bool isPause;
                bool isGameOver;
                bool isWin;
                bool isEnd;
        };
    };
};

#endif /* NIBBLER_HPP_ */