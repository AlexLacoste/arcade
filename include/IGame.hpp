/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "IDisplayModule.hpp"

class IGame {
    public:
        IGame();
        ~IGame();
        void init();
        void stop();
        void update();
        void changeLib(IDisplayModule &displayModule);

    protected:
    private:
};

#endif /* !IGAME_HPP_ */
