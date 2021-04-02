/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <memory>
#include <string>
#include <vector>
#include "../shared/Data.hpp"

namespace arcade
{
    namespace displayer
    {
        class IText {
          public:
            virtual ~IText() = default;
            virtual void setText(const std::string &text) = 0;
            virtual std::string getText() const = 0;
            virtual void setPosition(arcade::data::Vector2f pos) = 0;
            virtual arcade::data::Vector2f getPosition() const = 0;
            virtual void setFont(const std::string &font) = 0;
            virtual void setColor(arcade::data::Color color) = 0;
            virtual arcade::data::Color getColor() const = 0;
            virtual void setCharacterSize(unsigned int size) = 0;
            virtual arcade::data::FloatRect getLocalBounds() = 0;
            virtual void setOrigin(arcade::data::Vector2f origin) = 0;
            virtual arcade::data::Vector2f getOrigin() = 0;
        };

        class IDisplayModule {
          public:
            virtual ~IDisplayModule() = default;
//             enum AvailableOptions {
//                 NO_OPTIONS = 0,
//                 SET_CHARACTER_SIZE = 1 << 0,
//                 MOUSE_MOVE = 1 << 1,
//             };
// #define isOptions(disp, opt) ((disp)->availableOptions() & arcade::displayer::IDisplay::AvailableOptions::opt)

            // virtual int availableOptions() const = 0;
            virtual void init(
                const std::string &title = "Arcade", const unsigned int limit = 60) = 0;
            virtual void clearWindow() = 0;
            virtual void display() = 0;
            virtual void stop() = 0;
            virtual bool isOpen() const = 0;
            virtual void restartClock() = 0;
            virtual double getDeltaTime() = 0;
            virtual arcade::data::Vector2u getWindowSize() = 0;
            virtual std::vector<arcade::data::Event> getEvents() = 0;
            virtual void draw(std::unique_ptr<IText> &text) = 0;
            virtual std::unique_ptr<IText> createText(const std::string &text) = 0;
            virtual std::unique_ptr<IText> createText() = 0;
            
            // virtual arcade::data::KeyCode getLastKey() = 0;
        };
    } // namespace displayer
} // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
