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
#include "../../shared/IDisplayModule.hpp"
#include <chrono>
  
namespace sfml
{
    class TextSfml : public arcade::displayer::IText {
      public:
        TextSfml();
        TextSfml(const std::string &text);
        ~TextSfml();
        void setText(const std::string &text) override;
        std::string getText() const override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void setFont(const std::string &font) override;
        void setColor(arcade::data::Color color) override;
        arcade::data::Color getColor() const override;
        void setCharacterSize(unsigned int size) override;
        arcade::data::FloatRect getLocalBounds() const override;
        arcade::data::FloatRect getGlobalBounds() const override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() const override;
        sf::Text &getSfText();

      private:
        sf::Text text;
        sf::Font font;
    };

    class SpriteSfml : public arcade::displayer::ISprite {
      public:
        SpriteSfml();
        SpriteSfml(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale);
        ~SpriteSfml();
        void setSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite) override;
        void setPosition(arcade::data::Vector2f pos) override;
        arcade::data::Vector2f getPosition() const override;
        void move(arcade::data::Vector2f pos) override;
        void move(float x, float y) override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() const override;
        arcade::data::FloatRect getLocalBounds() const override;
        arcade::data::FloatRect getGlobalBounds() const override;
        void setScale(arcade::data::Vector2f scale) override;
        arcade::data::Vector2f getScale() const override;
        void rotate(float angle) override;
        void setRotation(float angle) override;
        float getRotation() const override;
        void setTextureRect(const arcade::data::IntRect &rect) override;
        arcade::data::IntRect getTextureRect() const override;
        void setColor(arcade::data::Color color,
            const std::vector<std::vector<arcade::data::Color>> &asciiColors) override;
        sf::Sprite &getSfSprite();
      private:
        sf::Sprite sprite;
        sf::Texture texture;
    };

    class GraphicSfml : public arcade::displayer::IDisplay {
      public:
        GraphicSfml();
        ~GraphicSfml();
        int availableOptions() const override;
        void init(const std::string &title = "Arcade", const unsigned int limit = 60) override;
        void stop() override;
        bool isOpen() const override;
        void clearWindow() override;
        void display() override;
        void restartClock() override;
        double getDeltaTime() const override;
        double getFrameDuration() const;
        arcade::data::Vector2u getWindowSize() const override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        void draw(std::unique_ptr<arcade::displayer::ISprite> &sprite) override;
        std::unique_ptr<arcade::displayer::IText> createText() const override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) const override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite() const override;
        std::unique_ptr<arcade::displayer::ISprite> createSprite(const std::string &spritePath, const std::vector<std::string> &asciiSprite, arcade::data::Vector2f scale = arcade::data::Vector2f{1, 1}) const override;

        double scaleMoveX(double time) const override;
        double scaleMoveY(double time) const override;

      private:
        sf::RenderWindow window;
        std::vector<arcade::data::Event> events;
        std::chrono::time_point<std::chrono::high_resolution_clock> chrono;
        double timeSinceLastFrame;
    };
} // namespace sfml

#endif /* !SFML_HPP_ */
