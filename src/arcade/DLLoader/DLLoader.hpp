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
                // throw ExceptionDLLoader{"Cannot open the library."}; // create exception
            }

            std::unique_ptr<T> (*start)() =
                (reinterpret_cast<std::unique_ptr<T> (*)()>(dlsym(this->handle, "entry_point")));

            if (!start) {
                // throw exception; // create exception
            }
            return (start)();
        }

      private:
        void *handle;
    };
} // namespace arcade

#endif /* !DLLOADER_HPP_ */
