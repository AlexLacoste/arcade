/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include "../include/DLLoader.hpp"

template <typename T>
arcade::DLLoader<T>::DLLoader(const char *path) : handle(dlopen(path, RTLD_LAZY))
{
    if (!this->handle || dlerror())
        throw exception; // create exception
}

template <typename T>
arcade::DLLoader<T>::~DLLoader()
{
    dlclose(this->handle);
}

template <typename T>
T *arcade::DLLoader<T>::getInstance()
{
    T *(*start)() = reinterpret_cast<T*(*)()>(dlsym(this->handle, "start"));

    if (!start)
        throw exception; // create exception
    return (*start)();
}