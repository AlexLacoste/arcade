/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLloader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

namespace arcade
{
    class DLLoader {
      public:
        DLLoader(const char *path);
        ~DLLoader();

        template <typename T>
        T *getInstance();

      private:
        void *handle;
    };
} // namespace arcade

#endif /* !DLLOADER_HPP_ */
