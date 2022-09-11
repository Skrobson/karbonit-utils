#pragma once 

#include <limits>
#include <type_traits>
//#include <concepts>

namespace skr::math
{
    
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value, T>:: type* = nullptr>
    T abs(T t)
    {
        return t < 0 ? -t : t; 
    };

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, T>::type* = nullptr>
    //template<std::floating_point T>
    bool epsilonEqual(T t1, T t2, T epsilon = std::numeric_limits<T>::epsilon())
    {
        return (abs(t1 - t2) < epsilon);
    };

}