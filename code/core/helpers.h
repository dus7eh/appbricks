/*
 * traits.h
 *
 *  Created on: Jun 21, 2018
 *      Author: Damian Ellwart
 */

#pragma once

#include <type_traits>
#include <memory>

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
#define B_CXX11
#endif
#if __cplusplus >= 201402L
#define B_CXX14
#endif

namespace bricks
{
    namespace core
    {
        template <bool cond, typename T = void>
        #ifndef B_CXX14
        using enable_if_t = typename std::enable_if<cond, T>::type;
        #else
        using enable_if_t = typename std::enable_if_t<cond, T>;
        #endif
        
        template <typename T, typename ... Args>
        std::unique_ptr<T> make_unique(Args&& ...args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
    }
}
