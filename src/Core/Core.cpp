/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Core
*/

#include "DLLoader.hpp"

#include "Core.hpp"

arcade::Core::Core(std::string libpath)
{
    try {
        DLLoader lib{libpath};
    } catch (arcade::ExceptionDLLoader &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "Core was created" << std::endl;
}

arcade::Core::~Core()
{
}
