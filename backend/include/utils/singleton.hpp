#pragma once

template <class T>
class makeSingleton
{
protected:
    makeSingleton() = default;
    virtual ~makeSingleton() = default;

public:
    makeSingleton(const makeSingleton &) = delete;
    makeSingleton &operator=(const makeSingleton &) = delete;

    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};