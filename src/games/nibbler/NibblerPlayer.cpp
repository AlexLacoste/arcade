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

void arcade::nibbler::Player::initPlayer(
    std::shared_ptr<arcade::displayer::IDisplay> &disp, const std::vector<std::string> &map)
{
    this->graphicLib = disp;
    int i = 0;
    int j = 0;

    if (this->snakeCell.empty()) {
        for (const auto &line : map) {
            if (line.find('0') != line.npos) {
                i = line.find('0');
                break;
            }
            j++;
        }
        if (static_cast<std::size_t>(j) == map.size())
            j = 0;
        this->snakeCell.emplace_back(Cell{'0', "ressources/nibbler/Snake_Head.bmp", i, j});
        this->direction = RIGHT;
        this->newDirection = RIGHT;
        this->timeSinceLastMove = 0.0f;
        this->size = 4;
        this->speed = 0.5f;
    }
    for (auto cell : this->snakeCell) {
        this->snakeSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
        std::vector<std::string> spriteCharacters{std::string{cell.getCharacter()}};
        std::unique_ptr<displayer::ISprite> &sprite = this->snakeSprite.at(this->snakeSprite.size() - 1);

        sprite = this->graphicLib->createSprite(cell.getImagePath(), spriteCharacters);
        sprite->setTextureRect(data::IntRect{0, 0, 50, 50});
        sprite->setOrigin({25, 25});
        sprite->setPosition({static_cast<float>(cell.getPosX() * sprite->getTextureRect().width + 25),
            static_cast<float>(cell.getPosY() * sprite->getTextureRect().height + 25)});
        sprite->setColor({255, 255, 255, 255}, this->colorSprite(1, 1, {0, 255, 0, 255}));
    }
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

const std::vector<arcade::nibbler::Cell> &arcade::nibbler::Player::getSnakeCell() const
{
    return this->snakeCell;
}

const std::vector<std::unique_ptr<arcade::displayer::ISprite>> &arcade::nibbler::Player::getSnakeSprite() const
{
    return this->snakeSprite;
}

bool arcade::nibbler::Player::move(const std::vector<std::vector<Cell>> &cellMap, double lastFrame)
{
    data::Vector2i vectorHead{this->snakeCell.at(0).getPos()};
    data::Vector2i vectorNew{vectorHead + this->getVectorMove(this->newDirection)};
    data::Vector2i vectorDirection{vectorHead + this->getVectorMove(this->direction)};

    this->timeSinceLastMove += lastFrame;
    if (this->timeSinceLastMove < this->speed) {
        return false;
    }
    for (const auto &cellLine : cellMap) {
        for (const auto &cell : cellLine) {
            if (cell.getPos() == vectorNew && cell.getCharacter() != '#') {
                this->moving(vectorNew);
                this->direction = this->newDirection;
                this->rotatePlayer();
                if (cell.getCharacter() == '*') {
                    return true;
                }
                return false;
            }
        }
    }
    for (const auto &cellLine : cellMap) {
        for (const auto &cell : cellLine) {
            if (cell.getPos() == vectorDirection && cell.getCharacter() != '#') {
                this->moving(vectorDirection);
                this->rotatePlayer();
                if (cell.getCharacter() == '*') {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

void arcade::nibbler::Player::moving(arcade::data::Vector2i vector)
{
    std::size_t i = 0;
    data::Vector2i stock{0, 0};

    for (i = 0; i < this->snakeCell.size(); i++) {
        stock = this->snakeCell.at(i).getPos();
        this->snakeCell.at(i).setPos(vector);
        this->snakeSprite.at(i)->setPosition(
            data::Vector2f{static_cast<float>(vector.x * this->snakeSprite.at(i)->getTextureRect().width + 25),
                static_cast<float>(vector.y * this->snakeSprite.at(i)->getTextureRect().height) + 25});
        vector = stock;
    }
    if (this->snakeCell.size() < this->size) {
        this->snakeCell.emplace_back('O', "ressources/nibbler/Snake_Body.bmp", vector);

        this->snakeSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
        std::vector<std::string> spriteCharacters{std::string{'O'}};
        std::unique_ptr<displayer::ISprite> &sprite = this->snakeSprite.at(this->snakeSprite.size() - 1);

        sprite = this->graphicLib->createSprite("ressources/nibbler/Snake_Body.bmp", spriteCharacters);
        sprite->setTextureRect(data::IntRect{0, 0, 50, 50});
        sprite->setOrigin({25, 25});
        sprite->setPosition({static_cast<float>(vector.x * sprite->getTextureRect().width + 25),
            static_cast<float>(vector.y * sprite->getTextureRect().height + 25)});
        sprite->setColor({255, 255, 255, 255}, this->colorSprite(1, 1, {0, 255, 0, 255}));
    }
    this->timeSinceLastMove = 0.f;
}

void arcade::nibbler::Player::stop()
{
    this->snakeSprite.clear();
}

void arcade::nibbler::Player::restart()
{
    this->snakeSprite.clear();
    this->snakeCell.clear();
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
    return (data::Vector2i{0, 0});
}

void arcade::nibbler::Player::upSize(size_t size)
{
    this->size += size;
}

void arcade::nibbler::Player::upSpeed()
{
    this->speed = this->speed * 9 / 10;
}

unsigned int arcade::nibbler::Player::eatFood(const std::vector<Cell> &foodSprite)
{
    unsigned int i = 0;

    for (; i < foodSprite.size(); i++) {
        if (foodSprite.at(i).getPos() == this->snakeCell.at(0).getPos()) {
            this->upSize(2);
            this->upSpeed();
            return (i + 1);
        }
    }
    return 0;
}

void arcade::nibbler::Player::draw()
{
    for (auto &sprite : this->snakeSprite) {
        this->graphicLib->draw(sprite);
    }
}

bool arcade::nibbler::Player::isEatHimself()
{
    std::vector<Cell>::iterator it = this->snakeCell.begin();

    for (it++; it != this->snakeCell.end(); it++) {
        if (this->snakeCell.at(0).getPos() == (*it).getPos()) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<arcade::data::Color>> arcade::nibbler::Player::colorSprite(
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

void arcade::nibbler::Player::rotatePlayer()
{
    switch (static_cast<int>(this->direction)) {
        case (UP):
            this->snakeSprite.at(0)->setRotation(270.f);
            break;
        case (DOWN):
            this->snakeSprite.at(0)->setRotation(90.f);
            break;
        case (LEFT):
            this->snakeSprite.at(0)->setRotation(180.f);
            break;
        case (RIGHT):
            this->snakeSprite.at(0)->setRotation(0.f);
            break;
    }
}