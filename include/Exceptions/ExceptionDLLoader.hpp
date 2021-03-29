/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** ExceptionDLLoader
*/

#ifndef EXCEPTIONDLLOADER_HPP_
#define EXCEPTIONDLLOADER_HPP_

#include "Exception.hpp"

namespace arcade {
    class ExceptionDLLoader : public Exception {
        public:
            ExceptionDLLoader(std::string const &message, std::string const &component = "DLLoader") : Exception(message, component) {};

        protected:
        private:
    };
}

#endif /* !EXCEPTIONDLLOADER_HPP_ */
