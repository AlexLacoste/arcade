/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** main
*/

#include "Core/Core.hpp"

int usage(const char *program)
{
    std::cout << "Usage: " << program << " [LIB]" << std::endl;
    return (0);
}

int arcade_func(const char *parameter)
{
    try {
        arcade::Core core{parameter};

        core.getLibraries();
    } catch (arcade::ExceptionCore &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return usage(argv[0]);
    }
    if (arcade_func(argv[1]) != 0) {
        return (84);
    }
    return (0);
}
