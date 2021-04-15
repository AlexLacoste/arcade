/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Errors
*/

#include "Errors.hpp"

arcade::errors::Error::Error(const std::string &msg) : _msg("Error: " + msg)
{
}

arcade::errors::Error::~Error()
{
}

const char *arcade::errors::Error::what() const noexcept
{
    return this->_msg.c_str();
}