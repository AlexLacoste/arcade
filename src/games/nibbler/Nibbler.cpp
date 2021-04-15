/*
** EPITECH PROJECT, 2020
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Nibbler.cpp
*/

#include <exception>
#include <fstream>
#include <iterator>
#include <string>
#include "Nibbler.hpp"

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
    if (this->gameMap.empty()) {
        this->getMap("ressources/nibbler/level_one.txt");
        this->initMap();
        this->time = 0;
        this->duration = 120;
        this->score = 0;
        this->isPause = false;
        this->isGameOver = false;
        this->isWin = false;
        this->isEnd = false;
    }
    this->initSpriteVector();
    this->player.initPlayer(disp, this->gameMap);
    this->initText();
}

arcade::games::GameStatus arcade::nibbler::Nibbler::update()
{
    this->handleEvents();
    if (this->isEnd)
        return arcade::games::GAME_ENDED;
    if (!this->isPause && !this->isGameOver && !this->isWin) {
        this->time += this->graphicLib->getDeltaTime();
        while (time > 1.0f) {
            this->duration -= 1;
            this->time -= 1;
        }
        if (this->duration == 0) {
            this->isGameOver = true;
        }
        if (!this->isGameOver && this->player.move(this->cellMap, this->graphicLib->getDeltaTime())) {
            this->eatFood(this->player.eatFood(this->foodMap));
        }
        if (this->player.isEatHimself()) {
            this->isGameOver = true;
        }
        if (this->foodMap.empty()) {
            this->score += 100 * this->duration;
            this->duration = 0;
            this->isWin = true;
        }
    }
    this->drawGame();
    return arcade::games::PLAYING;
}

void arcade::nibbler::Nibbler::stop()
{
    this->isPause = true;
    this->spriteMap.clear();
    this->foodSprite.clear();
    this->player.stop();
}

void arcade::nibbler::Nibbler::restart()
{
    this->isPause = true;
    this->gameMap.clear();
    this->cellMap.clear();
    this->spriteMap.clear();
    this->foodMap.clear();
    this->foodSprite.clear();
    this->player.restart();
    this->init(this->graphicLib);
}

unsigned int arcade::nibbler::Nibbler::getScore() const
{
    return this->score;
}

void arcade::nibbler::Nibbler::handleEvents()
{
    std::vector<arcade::data::Event> events = this->graphicLib->getEvents();

    for (auto &event : events) {
        if (event.type == arcade::data::EventType::KEY_PRESSED) {
            if ((this->isGameOver || this->isWin) && event.keyCode == arcade::data::SPACE)
                this->isEnd = true;
            switch (static_cast<int>(event.keyCode)) {
                case (arcade::data::SPACE):
                    this->isPause = (!this->isPause);
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
        throw errors::Error("Map path can't be open");
    while (std::getline(fs, line)) {
        this->gameMap.emplace_back(line);
    }
}

void arcade::nibbler::Nibbler::initMap()
{
    bool isAPlayer = false;
    int i = 0;
    int j = 0;

    for (const auto &line : this->gameMap) {
        i = 0;
        std::vector<Cell> cellLine{};
        for (const auto character : line) {
            if (character == '0') {
                if (!isAPlayer)
                    isAPlayer = true;
                else
                    throw errors::Error("Too much player on the map");
            }
            if (character == '#') {
                cellLine.emplace_back(Cell{'#', "ressources/nibbler/Wall.bmp", i, j});
            } else if (character == '*') {
                cellLine.emplace_back(Cell{'*', "ressources/nibbler/Food.bmp", i, j});
                foodMap.emplace_back(Cell{'*', "ressources/nibbler/Food.bmp", i, j});
            } else {
                cellLine.emplace_back(Cell{' ', "", i, j});
            }
            i++;
        }
        this->cellMap.emplace_back(cellLine);
        j++;
    }
    if (this->cellMap.size() == 0) {
        throw errors::Error("The map is empty");
    }
    if (!isAPlayer) {
        throw errors::Error("No player on the map");
    }
}

void arcade::nibbler::Nibbler::initSpriteVector()
{
    for (const std::vector<Cell> &line : this->cellMap) {
        std::vector<Cell> cellLine{};
        for (const Cell &cell : line) {
            if (cell.getCharacter() == '#') {
                this->spriteMap.emplace_back(std::unique_ptr<displayer::ISprite>());
                std::unique_ptr<displayer::ISprite> &sprite = this->spriteMap.back();
                std::vector<std::string> spriteCharacters{std::string{cell.getCharacter()}};

                sprite = this->graphicLib->createSprite(cell.getImagePath(), spriteCharacters);
                sprite->setTextureRect(data::IntRect{0, 0, 50, 50});
                sprite->setPosition({static_cast<float>(cell.getPosX() * sprite->getTextureRect().width),
                    static_cast<float>(cell.getPosY() * sprite->getTextureRect().height)});
                sprite->setColor(cell.getColor(), this->colorSprite(1, 1, {0, 255, 255, 255}));
            }
        }
    }
    for (const Cell &cell : this->foodMap) {
        this->foodSprite.emplace_back(std::unique_ptr<displayer::ISprite>());
        std::unique_ptr<displayer::ISprite> &sprite = this->foodSprite.back();
        std::vector<std::string> spriteCharacters{std::string{cell.getCharacter()}};

        sprite = this->graphicLib->createSprite(cell.getImagePath(), spriteCharacters);
        sprite->setTextureRect(data::IntRect{0, 0, 50, 50});
        sprite->setPosition({static_cast<float>(cell.getPosX() * sprite->getTextureRect().width),
            static_cast<float>(cell.getPosY() * sprite->getTextureRect().height)});
        sprite->setColor(cell.getColor(), this->colorSprite(1, 1, {255, 0, 0, 255}));
    }
}

void arcade::nibbler::Nibbler::drawGame()
{
    for (auto &sprite : this->spriteMap) {
        this->graphicLib->draw(sprite);
    }
    for (auto &sprite : this->foodSprite) {
        this->graphicLib->draw(sprite);
    }
    this->player.draw();
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
    this->highscoreText->setColor(data::Color{255, 255, 0, 255});
    this->highscoreText->setCharacterSize(17);
    this->highscoreText->setPosition(data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 70 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 20 / 100});

    this->timeText = this->graphicLib->createText("Time 0");
    this->timeText->setFont("ressources/font.ttf");
    this->timeText->setColor(data::Color{255, 255, 255, 255});
    this->timeText->setCharacterSize(17);
    this->timeText->setPosition(data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 70 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 30 / 100});

    this->messageText = this->graphicLib->createText("message");
    this->messageText->setFont("ressources/font.ttf");
    this->messageText->setColor(data::Color{255, 255, 255, 255});
    this->messageText->setCharacterSize(17);
    this->messageText->setPosition(data::Vector2f{static_cast<float>(this->graphicLib->getWindowSize().x) * 70 / 100,
        static_cast<float>(this->graphicLib->getWindowSize().y) * 40 / 100});
}

void arcade::nibbler::Nibbler::eatFood(unsigned int i)
{
    std::vector<Cell>::iterator it1 = this->foodMap.begin();
    std::vector<std::unique_ptr<displayer::ISprite>>::iterator it2 = this->foodSprite.begin();

    if (i == 0)
        return;
    for (unsigned int j = 1; j <= i; j++) {
        if (j == i) {
            this->foodMap.erase(it1);
            this->foodSprite.erase(it2);
            this->score += 600;
            return;
        }
        it1++;
        it2++;
    }
}

std::string arcade::nibbler::Nibbler::createTextNumber(const std::string &text, unsigned int score)
{
    std::ostringstream ss;

    ss << text << " " << score;
    return ss.str();
}

std::vector<std::vector<arcade::data::Color>> arcade::nibbler::Nibbler::colorSprite(
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