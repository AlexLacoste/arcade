/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLloader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <memory>
#include <string>

namespace arcade
{
    class DLLoader {
      public:
        DLLoader(std::string path);
        ~DLLoader();

        template <typename T>
        std::unique_ptr<T> getInstance(const std::string &ptr);

      private:
        void *handle;
    };
} // namespace arcade

#endif /* !DLLOADER_HPP_ */
