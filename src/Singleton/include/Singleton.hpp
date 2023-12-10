#pragma once
#include <utility>

namespace kit
{
template <typename T> class Singleton
{
  public:
    template <typename... Args> static T &getInstance(Args... args)
    {
        static T instance = T(std::forward<Args>(args)...);

        return instance;
    }

    Singleton(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton() = default;
};
} // namespace kit
