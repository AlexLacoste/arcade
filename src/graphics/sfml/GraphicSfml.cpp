/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include "Sfml.hpp"

extern "C" std::unique_ptr<sfml::GraphicSfml> entry_point()
{
    return std::make_unique<sfml::GraphicSfml>();
}

static const std::unordered_map<sf::Keyboard::Key, char> sfToArcadeKey{
    {sf::Keyboard::LBracket, '['},
    {sf::Keyboard::RBracket, ']'},
    {sf::Keyboard::Semicolon, ';'},
    {sf::Keyboard::Comma, ','},
    {sf::Keyboard::Period, '.'},
    {sf::Keyboard::Quote, '\''},
    {sf::Keyboard::Slash, '/'},
    {sf::Keyboard::Divide, '/'},
    {sf::Keyboard::Backslash, '\\'},
    {sf::Keyboard::Tilde, '~'},
    {sf::Keyboard::Equal, '='},
    {sf::Keyboard::Hyphen, '-'},
    {sf::Keyboard::Add, '+'},
    {sf::Keyboard::Subtract, '-'},
    {sf::Keyboard::Multiply, '*'},
    {sf::Keyboard::A, 'a'},
    {sf::Keyboard::B, 'b'},
    {sf::Keyboard::C, 'c'},
    {sf::Keyboard::D, 'd'},
    {sf::Keyboard::E, 'e'},
    {sf::Keyboard::F, 'f'},
    {sf::Keyboard::G, 'g'},
    {sf::Keyboard::H, 'h'},
    {sf::Keyboard::I, 'i'},
    {sf::Keyboard::J, 'j'},
    {sf::Keyboard::K, 'k'},
    {sf::Keyboard::L, 'l'},
    {sf::Keyboard::M, 'm'},
    {sf::Keyboard::N, 'n'},
    {sf::Keyboard::O, 'o'},
    {sf::Keyboard::P, 'p'},
    {sf::Keyboard::Q, 'q'},
    {sf::Keyboard::R, 'r'},
    {sf::Keyboard::S, 's'},
    {sf::Keyboard::T, 't'},
    {sf::Keyboard::U, 'u'},
    {sf::Keyboard::V, 'v'},
    {sf::Keyboard::W, 'w'},
    {sf::Keyboard::X, 'x'},
    {sf::Keyboard::Y, 'y'},
    {sf::Keyboard::Z, 'z'},
};

static const std::unordered_map<sf::Keyboard::Key, arcade::data::KeyCode> sfToArcadeKeyCode{
    {sf::Keyboard::Enter, arcade::data::KeyCode::ENTER},
    {sf::Keyboard::Backspace, arcade::data::KeyCode::BACKSPACE},
    {sf::Keyboard::Escape, arcade::data::KeyCode::ESCAPE},
    {sf::Keyboard::Space, arcade::data::KeyCode::SPACE},
    {sf::Keyboard::Down, arcade::data::KeyCode::DOWN},
    {sf::Keyboard::Up, arcade::data::KeyCode::UP},
    {sf::Keyboard::Left, arcade::data::KeyCode::LEFT},
    {sf::Keyboard::Right, arcade::data::KeyCode::RIGHT},
    {sf::Keyboard::Enter, arcade::data::KeyCode::ENTER},
};

static const std::unordered_map<sf::Event::EventType, arcade::data::EventType> sfToArcadeMouseType{
    {sf::Event::EventType::MouseButtonPressed, arcade::data::EventType::MOUSE_PRESSED},
    {sf::Event::EventType::MouseButtonReleased, arcade::data::EventType::MOUSE_RELEASED},
    {sf::Event::EventType::MouseMoved, arcade::data::EventType::MOUSE_MOVED},
};
static const std::unordered_map<sf::Mouse::Button, arcade::data::MouseBtn> sfToArcadeMouseBtn{
    {sf::Mouse::Button::Left, arcade::data::MouseBtn::BTN_1},
    {sf::Mouse::Button::Middle, arcade::data::MouseBtn::BTN_2},
    {sf::Mouse::Button::Right, arcade::data::MouseBtn::BTN_3},
};

sfml::GraphicSfml::GraphicSfml()
{
}

sfml::GraphicSfml::~GraphicSfml()
{
    if (this->window.isOpen())
        this->window.close();
}

int sfml::GraphicSfml::availableOptions() const
{
    return SET_CHARACTER_SIZE | MOUSE_MOVE | SETTING_FONTS;
}

bool sfml::GraphicSfml::isOpen() const
{
    return this->window.isOpen();
}

void sfml::GraphicSfml::init(const std::string &title, const unsigned int limit)
{
    this->window.create(sf::VideoMode(1920, 1080), title);
    this->window.setFramerateLimit(limit);
    this->restartClock();
}

void sfml::GraphicSfml::display()
{
    this->window.display();
    this->events.clear();
    this->timeSinceLastFrame = this->getFrameDuration();
    restartClock();
}

void sfml::GraphicSfml::stop()
{
    this->window.close();
}

void sfml::GraphicSfml::clearWindow()
{
    this->window.clear();
}

void sfml::GraphicSfml::restartClock()
{
    this->chrono = std::chrono::high_resolution_clock::now();
}

double sfml::GraphicSfml::getDeltaTime() const
{
    return this->timeSinceLastFrame;
}

double sfml::GraphicSfml::getFrameDuration() const
{
    return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
        std::chrono::high_resolution_clock::now() - this->chrono)
        .count();
}

arcade::data::Vector2u sfml::GraphicSfml::getWindowSize() const
{
    return arcade::data::Vector2u{this->window.getSize().x, this->window.getSize().y};
}

std::vector<arcade::data::Event> sfml::GraphicSfml::getEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->events.emplace_back(arcade::data::EventType::WINDOW_CLOSED,
                static_cast<arcade::data::EventType>(event.MouseButtonPressed));
        }
        if (event.type == sf::Event::KeyPressed) {
            if (sfToArcadeKey.find(event.key.code) != sfToArcadeKey.end()) {
                char c = static_cast<arcade::data::KeyCode>(sfToArcadeKey.at(event.key.code));
                int maj = (c >= 'a' && c <= 'z' && event.key.shift) ? 32 : 0;
                this->events.emplace_back(arcade::data::EventType::KEY_PRESSED, c - maj);
            } else if (sfToArcadeKeyCode.find(event.key.code) != sfToArcadeKeyCode.end()) {
                this->events.emplace_back(arcade::data::EventType::KEY_PRESSED,
                    static_cast<arcade::data::KeyCode>(sfToArcadeKeyCode.at(event.key.code)));
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (sfToArcadeMouseBtn.find(event.mouseButton.button)
                != sfToArcadeMouseBtn.end()) {
                this->events.emplace_back(arcade::data::EventType::MOUSE_PRESSED,
                    static_cast<arcade::data::MouseBtn>(
                        sfToArcadeMouseBtn.at(event.mouseButton.button)),
                    event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
    return this->events;
}

void sfml::GraphicSfml::draw(std::unique_ptr<arcade::displayer::IText> &text)
{
    this->window.draw(reinterpret_cast<std::unique_ptr<TextSfml> &>(text)->getSfText());
}

void sfml::GraphicSfml::draw(std::unique_ptr<arcade::displayer::ISprite> &sprite)
{
    this->window.draw(reinterpret_cast<std::unique_ptr<SpriteSfml> &>(sprite)->getSfSprite());
}

std::unique_ptr<arcade::displayer::IText> sfml::GraphicSfml::createText(const std::string &text) const
{
    return std::make_unique<TextSfml>(text);
}

std::unique_ptr<arcade::displayer::IText> sfml::GraphicSfml::createText() const
{
    return std::make_unique<TextSfml>();
}

std::unique_ptr<arcade::displayer::ISprite> sfml::GraphicSfml::createSprite() const
{
    return std::make_unique<SpriteSfml>();
}

std::unique_ptr<arcade::displayer::ISprite> sfml::GraphicSfml::createSprite(
    const std::string &spritePath, const std::vector<std::string> &asciiSprite,
    arcade::data::Vector2f scale) const
{
    return std::make_unique<SpriteSfml>(spritePath, asciiSprite, scale);
}

double sfml::GraphicSfml::scaleMoveX(double time) const
{
    if (time == 0) {
        return 0;
    }
    return (getWindowSize().x / time) / (1.0f / getDeltaTime());
}

double sfml::GraphicSfml::scaleMoveY(double time) const
{
    if (time == 0) {
        return 0;
    }
    return (getWindowSize().y / time) / (1.0f / getDeltaTime());
}