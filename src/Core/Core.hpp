/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "DLLoader/DLLoader.hpp"
#include "Exceptions/ExceptionDLLoader.hpp"
#include "Exceptions/ExceptionCore.hpp"

namespace arcade
{
    class Core {
        public:
            Core(std::string libpath);
            ~Core();

            void getLibraries();

        protected:
        private:
            std::vector<std::string> librairies;
    };
}

#endif /* !CORE_HPP_ */
