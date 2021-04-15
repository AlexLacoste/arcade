/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLloader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <memory>
#include <string>
#include "../../shared/Errors.hpp"

namespace arcade
{
    class DLLoader {
      public:
        DLLoader(std::string path)
        {
            this->handle = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
        }

        ~DLLoader()
        {
            dlclose(this->handle);
        }

        template <typename T>
        std::unique_ptr<T> getInstance()
        {
            if (!this->handle || dlerror()) {
                throw errors::Error{"Cannot open the library."};
            }

            std::unique_ptr<T> (*start)() =
                (reinterpret_cast<std::unique_ptr<T> (*)()>(dlsym(this->handle, "entry_point")));

            if (!start) {
                throw errors::Error{"Cannot find the entry_point"};
            }
            return (start)();
        }

      private:
        void *handle;
    };
} // namespace arcade

#endif /* !DLLOADER_HPP_ */
