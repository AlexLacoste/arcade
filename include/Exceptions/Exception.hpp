/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <iostream>

namespace arcade {
    class Exception : std::exception {
        public:
            Exception(std::string const &message, std::string const &component = "Unknown") : message(message), component(component) {};
            virtual ~Exception() {};

            const std::string &getComponent() const { return this->component; };
            const char *what() const noexcept override { return this->message.c_str(); };

        protected:
            std::string message;
            std::string component;
        private:
    };
}


#endif /* !EXCEPTION_HPP_ */
