/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <vector>
#include "../../include/Keys.hpp"

namespace arcade
{
    class IDisplayModule {
      public:
        virtual ~IDisplayModule() = default;
        virtual bool isOpen() const = 0;
        virtual std::vector<struct> getEvent() = 0;
        virtual void display() = 0;
        virtual void init(const std::string &title) = 0;
        virtual void stop() = 0;
        virtual void clearWindow() = 0;
        virtual Keys getLastKey() = 0;
    };
} // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
