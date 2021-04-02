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
#include "../IDisplayModule.hpp"

namespace ncurses
{
    class TextNcurses : public arcade::displayer::IText {
      public:
        TextNcurses();
        TextNcurses(const std::string &text);
        ~TextNcurses() override;
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
      private:
        std::string str;
        arcade::data::Vector2f pos;
        arcade::data::Color color;
    };
    class GraphicNcurses : public arcade::displayer::IDisplayModule {
      public:
        GraphicNcurses();
        ~GraphicNcurses() override;
        bool isOpen() const override;
        void display() override;
        void init(
            const std::string &title = "Arcade", const unsigned int limit = 60) override;
        void stop() override;
        void clearWindow() override;
        void restartClock() override;
        double getDeltaTime() override;
        arcade::data::Vector2u getWindowSize() override;
        std::vector<arcade::data::Event> getEvents() override;
        void draw(std::unique_ptr<arcade::displayer::IText> &text) override;
        std::unique_ptr<arcade::displayer::IText> createText(const std::string &text) override;
        std::unique_ptr<arcade::displayer::IText> createText() override;

        // arcade::data::KeyCode getLastKey() override;
      private:
        bool windowIsOpen;
    };
} // namespace ncurses

#endif /* !SFML_HPP_ */
