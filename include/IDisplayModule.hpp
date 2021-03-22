/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>

namespace arcade {
  class IDisplayModule {
    public:
      virtual ~IDisplayModule() = default;
      virtual bool isOpen() const = 0;
      virtual bool pollEvent() = 0;
      virtual void display() = 0;
      virtual void openRenderWindow(const std::string &title) = 0;
      virtual void closeRenderWindow() = 0;
      virtual void clearRenderWindow() = 0;
  };
}

#endif /* !IDISPLAYMODULE_HPP_ */
