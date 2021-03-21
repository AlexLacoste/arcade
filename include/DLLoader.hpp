/*
** EPITECH PROJECT, 2021
** B-OOP-400-BDX-4-1-arcade-alexandre.lacoste
** File description:
** DLloader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

template <typename T>
class DLLoader {
  public:
    DLLoader(const char *path);
    ~DLLoader();
    T *getInstance();

  private:
    void *handle;
};

#endif /* !DLLOADER_HPP_ */
