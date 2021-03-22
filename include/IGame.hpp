/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "IDisplayModule.hpp"
#include "Keys.hpp"

namespace arcade {
  class IGame {
    public:
      virtual ~IGame() = 0;
      virtual void init() = 0;
      virtual void stop() = 0;
      virtual void update() = 0;
      virtual void changeLib(IDisplayModule &displayModule) = 0;
      virtual Keys getLastKey() = 0;

    protected:
    private:
  };
}

#endif /* !IGAME_HPP_ */
