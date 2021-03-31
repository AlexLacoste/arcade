/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLLoader
*/

#include <dlfcn.h>
#include "DLLoader.hpp"

arcade::DLLoader::DLLoader(std::string path)
{
    this->handle = dlopen(path.c_str(), RTLD_LAZY);
}

arcade::DLLoader::~DLLoader()
{
    dlclose(this->handle);
}

template <typename T>
std::unique_ptr<T> arcade::DLLoader::getInstance()
{
    if (!this->handle || dlerror()) {
        throw ExceptionDLLoader{"Cannot open the library."}; // create exception
    }

    std::unique_ptr<T> (*start)()(reinterpret_cast<T *(*)()>(dlsym(this->handle, "entry_point")));

    if (!start)
        throw exception; // create exception
    return (start)();
}
