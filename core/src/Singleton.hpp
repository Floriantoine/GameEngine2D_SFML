/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Singleton class
*/

#pragma once

namespace Game {

template <class T> class Singleton {
  public:
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;

    static T &getInstance()
    {
        static Instance instance;

        return instance;
    };

  protected:
    Singleton(){};

  private:
    struct Instance : public T
    {
        Instance() : T()
        {
        }
    };
};

} // namespace Game