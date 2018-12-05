/*
 * timing.h
 *
 *  Created on: Dec 02, 2018
 *      Author: Damian Ellwart
 */

#pragma once
#include <chrono>
#include <functional>
#include "optional.h"

namespace bricks {
    namespace core {
        class TimeMeasure {
        public:
            using TimeResult = std::chrono::nanoseconds;

            template<typename T>
            struct MeasureResult {
                TimeResult time;
                Optional<T> result;
            };

            template<>
            struct MeasureResult<void> {
                TimeResult time;
            };

            template <typename Func, typename ... Args, typename Ret = decltype(std::declval<Func>()(std::declval<Args>()...)), typename E = enable_if_t<!std::is_same<void, Ret>::value>>
            static MeasureResult<Ret> measure(Func func, Args ...args) {
                const auto start = std::chrono::steady_clock::now();
                auto res = func(std::forward<Args>(args)...);
                const auto end = std::chrono::steady_clock::now();

                return { std::chrono::duration_cast<TimeResult>(end - start), std::forward<Ret>(res) };
            }

            template <typename Func, typename ... Args, typename Ret = decltype(std::declval<Func>()(std::declval<Args>()...)), typename E = enable_if_t<std::is_same<void, Ret>::value>>
            static MeasureResult<void> measure(Func func, Args ...args) {
                const auto start = std::chrono::steady_clock::now();
                func(std::forward<Args>(args)...);
                const auto end = std::chrono::steady_clock::now();

                return { std::chrono::duration_cast<TimeResult>(end - start) };
            }

        private: 
        };
    }
}
