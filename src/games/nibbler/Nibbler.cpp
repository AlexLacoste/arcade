/*
** EPITECH PROJECT, 2020
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Nibbler.cpp
*/

#include "Nibbler.hpp"
#include <exception>
#include <fstream>
#include <iterator>
#include <string>

extern "C" std::unique_ptr<arcade::games::IGame> entry_point()
{
    return std::make_unique<arcade::nibbler::Nibbler>();
}

arcade::nibbler::Nibbler::Nibbler()
{
}

arcade::nibbler::Nibbler::~Nibbler()
{
}

void arcade::nibbler::Nibbler::init(std::shared_ptr<displayer::IDisplay> &disp)
{
    this->graphicLib = disp;
    this->getMap("ressources/nibbler/level_one.txt");
    this->initMap();
    this->initSpriteVector();
    this->player.initPlayer(this->gameMap);
    this->time = 0;
    this->duration = 120;
    this->score = 0;
    this->initText();
    this->isPause = false;
    this->isGameOver = false;
    this->isWin = false;
}

arcade::games::GameStatus arcade::nibbler::Nibbler::update()
{
    this->handleEvents();
    if (this->isEnd)
        return arcade::games::GAME_ENDED;
    if (!this->isPause && !this->isGameOver && !this->isWin) {
        this->time += this->graphicLib->getDeltaTime();
        while (time > 1.0f) {
            duration -= 1;
            time -= 1;
        }
        if (!this->player.move(this->cellMap, this->graphicLib->getDeltaTime())) {
            this->isGameOver = true;
        }
        if (this->foodMap.empty()) {
            this->isWin = true;
        }
    }
    this->drawGame();
    return arcade::games::PLAYING;
}

void arcade::nibbler::Nibbler::stop()
{
    this->isPause = (!this->isPause);
}

void arcade::nibbler::Nibbler::restart()
{
}

unsigned int arcade::nibbler::Nibbler::getScore() const
{
    return this->score;
}

void arcade::nibbler::Nibbler::handleEvents()
{
    std::vector<arcade::data::Event> events = this->graphicLib->getEvents();

    for (auto event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            switch (static_cast<int>(event.keyCode)) {
                case (arcade::data::SPACE):
                    this->player.setDirection(Player::RIGHT);
                    break;
                case (arcade::data::UP):
                    this->player.setDirection(Player::UP);
                    break;
                case (arcade::data::DOWN):
                    this->player.setDirection(Player::DOWN);
                    break;
                case (arcade::data::LEFT):
                    this->player.setDirection(Player::LEFT);
                    break;
                case (arcade::data::RIGHT):
                    this->player.setDirection(Player::RIGHT);
                    break;
            }
        }
    }
}

void arcade::nibbler::Nibbler::getMap(const std::string &mapPath)
{
    std::ifstream fs{mapPath};
    std::string line{};

    if (!fs.is_open())
        throw std::exception();
    while (std::getline(fs, line)) {
        this->gameMap.emplace_back(line);
    }
}

void arcade::nibbler::Nibbler::initMap()
{
    bool isAPlayer = false;
    int i = 0;
    int j = 0;

    for (const auto line: this->gameMap) {
        i = 0;
        std::vector<Cell> cellLine{};
        for (const auto character: line) {
            if (character == '0') {
                if (!isAPlayer)
                    isAPlayer = true;
                else
                    throw std::exception();
            }
            if (character == '#') {
                cellLine.emplace_back(Cell{'#', "ressources/nibbler/Wall.bmp", i, j});
            } else if (character == '*') {
                cellLine.emplace_back(Cell{'*', "ressources/nibbler/Food.bmp", i, j});
            } else {
                cellLine.emplace_back(Cell{' ', "", i, j});
            }
            i++;
        }
        this->cellMap.emplace_back(cellLine);
        j++;
    }
    if (this->cellMap.size() == 0) {
        throw std::exception();
    }
    if (!isAPlayer) {
        throw std::exception();
    }
}

void arcade::nibbler::Nibbler::initSpriteVector()
{
    int i = 0;
    int j = 0;

    for (const std::vector<Cell>line: this->cellMap) {
        i = 0;
        std::vector<Cell> cellLine{};
        for (const Cell cell: line) {
            if (cell.getCharacter() != ' ') {
                this->spriteMap.emplace_back(std::unique_ptr<displayer::ISprite>());
                std::unique_ptr<displayer::ISprite> &sprite = this->spriteMap.at(this->spriteMap.size() - 1);
                std::vector<std::string> spriteCharacters{std::string{cell.getCharacter()}};

                sprite = this->graphicLib->createSprite(cell.getImagePath(), spriteCharacters);
                sprite->setTextureRect(data::IntRect{0, 0, 50, 50});
                sprite->setPosition({static_cast<float>(cell.getPosX() + i * sprite->getTextureRect().width), static_cast<float>(cell.getPosY() + j * sprite->getTextureRect().height)});
                sprite->setColor(cell.getColor(), this->colorSprite(1, 1, cell.getColor()));
            }
            i++;
        }
        j++;
    }
}

void arcade::nibbler::Nibbler::drawGame()
{
    for (auto &sprite: this->spriteMap) {
        this->graphicLib->draw(sprite);
    }
    // for (const auto cell: this->player.getPlayer()) {
    //     std::unique_ptr<displayer::ISprite> sprite = this->graphicLib->createSprite(cell.getImagePath(), std::vector<std::string>{std::string{cell.getCharacter()}},cell.getPos());
    //     color.at(0).at(0) = cell.getColor();
    //     sprite->setColor(cell.getColor(), color);
    //     // this->graphicLib->draw(sprite);
    // }
    this->highscoreText->setText(this->createTextNumber("Highscore ", this->score));
    this->graphicLib->draw(highscoreText);
    this->timeText->setText(this->createTextNumber("Time ", this->duration));
    this->graphicLib->draw(timeText);
    if (this->isWin) {
        this->messageText->setText("You WIN !");
        this->graphicLib->draw(messageText);
    } else if (this->isGameOver) {
        this->messageText->setText("GAME OVER !");
        this->graphicLib->draw(messageText);
    } else if (this->isPause) {
        this->messageText->setText("Pause =");
        this->graphicLib->draw(messageText);
    }
}

void arcade::nibbler::Nibbler::initText()
{
    this->highscoreText = this->graphicLib->createText("Highscore 0");
    this->highscoreText->setFont("ressources/font.ttf");
    this->highscoreText->setCharacterSize(17);
    this->highscoreText->setColor(data::Color{255, 255, 255, 255});
    this->highscoreText->setPosition({static_cast<float>((this->graphicLib->getWindowSize().x) / 2) * 50 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});

    this->timeText = this->graphicLib->createText("Time 0");
    this->timeText->setFont("ressources/font.ttf");
    this->timeText->setCharacterSize(17);
    this->timeText->setColor(data::Color{255, 255, 255, 255});
    this->timeText->setPosition({static_cast<float>((this->graphicLib->getWindowSize().x) / 2) * 100 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});

    this->messageText = this->graphicLib->createText("message");
    this->messageText->setFont("ressources/font.ttf");
    this->messageText->setCharacterSize(17);
    this->timeText->setColor(data::Color{255, 255, 255, 255});
    this->timeText->setPosition({static_cast<float>((this->graphicLib->getWindowSize().x) / 2),
        static_cast<float>(this->graphicLib->getWindowSize().y) / 2});
}

std::string arcade::nibbler::Nibbler::createTextNumber(const std::string &text, unsigned int score)
{
    std::ostringstream ss;

    ss << text << " " << score;
    return ss.str();
}

std::vector<std::vector<arcade::data::Color>> arcade::nibbler::Nibbler::colorSprite(std::size_t i, std::size_t j, arcade::data::Color color)
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