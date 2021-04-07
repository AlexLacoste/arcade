/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <memory>

#include "IGame.hpp"

namespace pacman
{
    class Pacman : public IGame {
        public:
            Pacman();
            ~Pacman();

            void init() override;
            void stop() override;
            void pause() override;
            void resume() override;
            void update() override;
            void handleEvent(const std::vector<arcade::data::Event> &event) override;
            void changeHighScore() override;

        protected:
        private:
    };
}

#endif /* !PACMAN_HPP_ */