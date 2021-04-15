/*
** EPITECH PROJECT, 2020
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"

arcade::nibbler::Player::Player()
{
}

arcade::nibbler::Player::~Player()
{
}

void arcade::nibbler::Player::initPlayer(const std::vector<std::string> &map)
{
    int i = 0;
    int j = 0;

    for (const auto line: map) {
        if (line.find('0') != line.npos) {
            j = line.find('0');
            break;
        }
        i++;
    }
    if (static_cast<std::size_t>(i) == map.size())
        i = 0;
    this->snakeBody.emplace_back(Cell{'0', "ressources/nibbler/Snake_Head.bmp", i, j});
    this->direction = LEFT;
    this->newDirection = LEFT;
    this->timeSinceLastMove = 0.0f;
    this->size = 4;
}

arcade::nibbler::Player::Direction arcade::nibbler::Player::getDirection() const
{
    return this->direction;
}

void arcade::nibbler::Player::setDirection(Direction direct)
{
    if (direct == UP && this->direction != DOWN) {
        this->newDirection = direct;
    } else if (direct == DOWN && this->direction != UP) {
        this->newDirection = direct;
    } else if (direct == LEFT && this->direction != RIGHT) {
        this->newDirection = direct;
    } else if (direct == RIGHT && this->direction != LEFT) {
        this->newDirection = direct;
    }
}

const std::vector<arcade::nibbler::Cell> &arcade::nibbler::Player::getPlayer() const
{
    return this->snakeBody;
}

bool arcade::nibbler::Player::move(std::vector<std::vector<Cell>> &cellMap, double lastFrame)
{
    data::Vector2i vectorHead {this->snakeBody.at(this->snakeBody.size() - 1).getPos()};
    data::Vector2i vectorDirection {this->getVectorMove(this->direction)};
    data::Vector2i vectorNew {this->getVectorMove(this->newDirection)};

    this->timeSinceLastMove += lastFrame;
    if (this->timeSinceLastMove > 1.0f) {
        if (cellMap.at(vectorHead.x).at(vectorHead.y - 1).getCharacter() == ' ') {
            vectorHead.y += -1;
            this->direction = UP;
            this->newDirection = UP;
        } else if (cellMap.at(vectorHead.x).at(vectorHead.y + 1).getCharacter() == ' ') {
            vectorHead.y += 1;
            this->direction = DOWN;
            this->newDirection = DOWN;
        } else if (cellMap.at(vectorHead.x - 1).at(vectorHead.y).getCharacter() == ' ') {
            vectorHead.x += -1;
            this->direction = LEFT;
            this->newDirection = LEFT;
        } else if (cellMap.at(vectorHead.x + 1).at(vectorHead.y).getCharacter() == ' ') {
            vectorHead.x += 1;
            this->direction = RIGHT;
            this->newDirection = RIGHT;
        } else {
            return (false);
        }
    } else if (cellMap.at(vectorHead.x + vectorNew.x).at(vectorHead.y + vectorNew.x).getCharacter() == ' ') {
        vectorHead.x += vectorNew.x;
        vectorHead.y += vectorNew.y;
        this->direction = this->newDirection;
    } else if (cellMap.at(vectorHead.x + vectorDirection.x).at(vectorHead.y + vectorDirection.x).getCharacter() == ' ') {
        vectorHead.x += vectorDirection.x;
        vectorHead.y += vectorDirection.y;
    } else {
        return true;
    }
    this->snakeBody.emplace_back(Cell{'0', "ressources/nibbler/Snake_Head.bmp", vectorHead});
    this->snakeBody.at(this->snakeBody.size() - 2).setCharacter('0');
    this->snakeBody.at(this->snakeBody.size() - 2).setImagePath("ressources/nibbler/Snake_Body.bmp");
    this->timeSinceLastMove = 0.0f;
    while (this->snakeBody.size() > size) {
        this->snakeBody.erase(this->snakeBody.begin());
    }
    return true;
}

arcade::data::Vector2i arcade::nibbler::Player::getVectorMove(arcade::nibbler::Player::Direction direction) const
{
    switch (static_cast<int>(direction)) {
        case (UP):
            return (data::Vector2i{0, -1});
        case (DOWN):
            return (data::Vector2i{0, 1});
        case (LEFT):
            return (data::Vector2i{-1, 0});
        case (RIGHT):
            return (data::Vector2i{1, 0});
    }
    return (data::Vector2i{1, 0});
}

void arcade::nibbler::Player::upSize(size_t size)
{
    this->size += size;
}