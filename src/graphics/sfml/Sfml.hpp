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
#include <SFML/Window/Event.hpp>
#include "../IDisplayModule.hpp"
#include <unordered_map>

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
        arcade::data::FloatRect getLocalBounds() override;
        void setOrigin(arcade::data::Vector2f origin) override;
        arcade::data::Vector2f getOrigin() override;
        sf::Text &getSfText();

      private:
        sf::Text text;
        sf::Font font;
    };

    // class ISprite {
    //   public:
    //     ISprite();
    //     ISprite(const std::string &text);
    //     ~ISprite();
    //     void setSprite(const std::string &spritePath, const std::vector<std::string>
    //     &asciiSprite); void setPosition(arcade::data::Vector2f pos); arcade::data::Vector2f
    //     getPosition() const; void move(arcade::data::Vector2f pos); void move(float x, float y);
    //     void setOrigin(arcade::data::Vector2f origin);
    //     arcade::data::Vector2f getOrigin();
    //     arcade::data::FloatRect getLocalBounds();
    //     void setScale(arcade::data::Vector2f scale);
    //     arcade::data::Vector2f getScale();
    //     float getRotation();
    //     void setRotation(float angle);
    //     void rotate(float anle);
    //     void setTextureRect(const arcade::data::IntRect &rect);
    //     arcade::data::IntRect getTextureRect() const;
    //     void setColor(arcade::data::Color color,
    //         const std::vector<std::vector<arcade::data::Color>> &asciiColors);
    // };

    class GraphicSfml : public arcade::displayer::IDisplay {
      public:
        GraphicSfml();
        ~GraphicSfml();
        bool isOpen() override;
        void display() override;
        void init(const std::string &title = "Arcade", const unsigned int limit = 60) override;
        void stop() override;
        void clearWindow() override;
        void restartClock() override;
        double getDeltaTime() override;
        arcade::data::Vector2u getWindowSize() override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) override;
        std::unique_ptr<arcade::displayer::IText> createText() override;

        double scaleMoveX(double time) override;
        double scaleMoveY(double time) override;

        // arcade::data::KeyCode getLastKey() override;
      private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        sf::Time time;
        std::vector<arcade::data::Event> events;
    };
} // namespace sfml

#endif /* !SFML_HPP_ */
