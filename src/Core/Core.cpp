/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Core
*/

#include <filesystem>
#include <regex>

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

void arcade::Core::getLibraries()
{
    std::string libpath{"./lib/"};
    std::regex reg{"./lib/arcade_[a-z]+.so"};

    for (const auto &file : std::filesystem::directory_iterator(libpath)) {
        std::string filename{file.path()};

        if (std::regex_match(filename, reg) == false) {
            std::cout << "Not valid library " + filename + " in " + libpath + " directory" << std::endl;
        } else {
            this->librairies.push_back(filename);
        }
    }
}
