/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <memory>
#include "../shared/IDisplayModule.hpp"
#include "../shared/Data.hpp"

namespace arcade
{
    class IGame {
      public:
        virtual void init(std::shared_ptr<displayer::IDisplay> &disp) = 0; // maybe call it reloadDisplayer and create a second func initGame which just set pos lives and etc
        // virtual void restart() = 0;
        virtual void update() = 0; // return enum game state
        virtual void stop() = 0;
        // virtual int getScore() = 0; for the arcade to store the score if it is a high score

      protected:
      private:
    };
} // namespace arcade

#endif /* !IGAME_HPP_ */

// #include "Games.hpp"

// class Game1 : public arcade::games::IGame {
//     public:

//     private:
//         std::shared_ptr<arcade::displayer::IDisplay> _displayer;
//         std::unique_ptr<arcade::displayer::IText> _tmp;
// };

// #endif /* !GAME1_HPP_ */
