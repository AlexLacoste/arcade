/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Pacman
*/

#include "Pacman.hpp"

extern "C" std::unique_ptr<pacman::Pacman> entry_point()
{
    return std::make_unique<pacman::Pacman>();
}

pacman::Pacman::Pacman()
{
    std::cout << "Class Pacman was created!" << std::endl;
}

pacman::Pacman::~Pacman()
{
}
