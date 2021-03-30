/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** main
*/

#include "Core/Core.hpp"

int main(int argc, char **argv)
{
    if (argv[1] != NULL) {
        arcade::Core core{std::string{argv[1]}};

        std::cout << "Main program" << std::endl;
    }
    return (0);
}
