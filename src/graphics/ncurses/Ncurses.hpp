/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <chrono>
#include "../../shared/IDisplayModule.hpp"

namespace ncurses
{
    class TextNcurses : public arcade::displayer::IText {
      public:
        TextNcurses();
        TextNcurses(const std::string &text);
        ~TextNcurses();
        void setText(const std::string &text) override;
        std::string getText() const override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void setFont(const std::string &font) override;
        void setColor(arcade::data::Color color) override;
        arcade::data::Color getColor() const override;
        void setCharacterSize(unsigned int size) override;
        arcade::data::FloatRect getLocalBounds() override;
        arcade::data::FloatRect getGlobalBounds() override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;
      private:
        std::string str;
        arcade::data::Vector2f pos;
        arcade::data::Color color;
    };

    class SpriteNcurses : public arcade::displayer::ISprite {
      public:
        SpriteNcurses();
        SpriteNcurses(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale);
        ~SpriteNcurses();
        void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void move(arcade::data::Vector2f pos) override;
        void move(float x, float y) override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;
        arcade::data::FloatRect getLocalBounds() override;
        arcade::data::FloatRect getGlobalBounds() override;
        void setScale(arcade::data::Vector2f scale) override;
        arcade::data::Vector2f getScale() override;
        void rotate(float anle) override;
        void setRotation(float angle) override;
        float getRotation() override;
        void setTextureRect(const arcade::data::IntRect &rect) override;
        arcade::data::IntRect getTextureRect() const override;
        void setColor(arcade::data::Color color,
            const std::vector<std::vector<arcade::data::Color>> &asciiColors) override;
        std::vector<std::string> getSpriteNcurses();
      private:
        std::vector<std::string> sprite;
        arcade::data::Vector2f pos;
        arcade::data::Vector2f origin;
        float rotation;
    };

    class GraphicNcurses : public arcade::displayer::IDisplay {
      public:
        GraphicNcurses();
        ~GraphicNcurses();
        int availableOptions() const override;
        void init(
            const std::string &title = "Arcade", const unsigned int limit = 60) override;
        void stop() override;
        bool isOpen() override;
        void clearWindow() override;
        void display() override;
        void restartClock() override;
        double getDeltaTime() override;
        double getFrameDuration() const;
        arcade::data::Vector2u getWindowSize() override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        void draw(std::unique_ptr<arcade::displayer::ISprite> &sprite) override;
        std::unique_ptr<arcade::displayer::IText> createText() override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite() override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) override;

        double scaleMoveX(double time) override;
        double scaleMoveY(double time) override;

        // arcade::data::KeyCode getLastKey() override;
      private:
        bool windowIsOpen;
        bool hasColors;
        bool eventFrame;
        std::vector<arcade::data::Event> events;
        std::chrono::time_point<std::chrono::high_resolution_clock> time;
        double lastFrameTime;
        unsigned int frameLimit;
    };
} // namespace ncurses

#endif /* !SFML_HPP_ */
