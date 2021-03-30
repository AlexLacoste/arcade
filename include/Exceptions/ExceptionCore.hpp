/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** ExceptionCore
*/

#ifndef EXCEPTIONCORE_HPP_
#define EXCEPTIONCORE_HPP_

#include "Exception.hpp"

namespace arcade {
    class ExceptionCore : public Exception {
        public:
            ExceptionCore(std::string const &message, std::string const &component = "Core") : Exception(message, component) {};

        protected:
        private:
    };
}

#endif /* !EXCEPTIONCORE_HPP_ */
