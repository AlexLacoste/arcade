/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include "../../include/Keys.hpp"

namespace arcade
{
    class IGame {
      public:
        virtual ~IGame() = 0;
        virtual void init() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual void update() = 0;
        virtual void handleEvent(const std::vector<Keys> &keys) = 0;
        virtual void changeHighScore() = 0;

      protected:
      private:
    };
} // namespace arcade

#endif /* !IGAME_HPP_ */
