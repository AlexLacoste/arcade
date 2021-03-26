/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include "../include/DLLoader.hpp"

arcade::DLLoader::DLLoader(const char *path) : handle(dlopen(path, RTLD_LAZY))
{
}

arcade::DLLoader::~DLLoader()
{
    dlclose(this->handle);
}

template <typename T> T *arcade::DLLoader::getInstance()
{
    if (!this->handle || dlerror())
        throw exception; // create exception

    T *(*start)() = reinterpret_cast<T *(*)()>(dlsym(this->handle, "start"));

    if (!start)
        throw exception; // create exception
    return (*start)();
}
