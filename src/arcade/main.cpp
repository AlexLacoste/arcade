/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** main
*/

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "Arcade.hpp"

bool badEnv(char **env)
{
    if (!env[0])
        return true;
    for (int i = 0; env[i]; i++) {
        if (strcmp(env[i], "DISPLAY=:0") == 0)
            return false;
    }
    return true;
}

int main(int ac, char **av, char **env)
{
    // TODO: check env
    if (ac != 2) {
        std::cerr << "Usage : " << av[0] << "lib/[lib_name].so" << std::endl;
        return (84);
    }

    // if (badEnv(env)) {
    //     std::cerr << "Cannot launch " << av[0] << ", env is not ready." << std::endl;
    //     return 84;
    // }

    std::unique_ptr<arcade::Arcade> core = std::make_unique<arcade::Arcade>(av[1]);
    try {
        core->run();
    }
    // catch (Errors &e) { 
    //     std::cerr << e.what() << std::endl; 
    //     return (84);
    // }
    catch (...) {
        std::cerr << "An error has occured." << std::endl;
        return (84);
    }
    return 0;
}
