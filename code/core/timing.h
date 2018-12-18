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
    namespace bench {
        namespace {
            using TimeResult = std::chrono::nanoseconds;

            template <typename Func, typename ...Args>
            using FuncReturn = decltype(std::declval<Func>()(std::declval<Args>()...));
        }

        template<typename T>
        struct MeasureResult {
            TimeResult time;
            core::Optional<T> result;
        };

        template<>
        struct MeasureResult<void> {
            TimeResult time;
        };

        template <typename Func, typename ...Args, typename Ret = FuncReturn<Func, Args...>, typename E = enable_if_t<!std::is_void<Ret>::value>>
        static MeasureResult<Ret> func_bench(Func&& func, Args&& ...args) {
            const auto start = std::chrono::steady_clock::now();
            auto res = func(std::forward<Args>(args)...);
            const auto end = std::chrono::steady_clock::now();

            return{ std::chrono::duration_cast<TimeResult>(end - start), std::forward<Ret>(res) };
        }

        template <typename Func, typename ...Args, typename Ret = FuncReturn<Func, Args...>, typename E = enable_if_t<std::is_void<Ret>::value>>
        static MeasureResult<void> func_bench(Func&& func, Args&& ...args) {
            const auto start = std::chrono::steady_clock::now();
            func(std::forward<Args>(args)...);
            const auto end = std::chrono::steady_clock::now();

            return{ std::chrono::duration_cast<TimeResult>(end - start) };
        }

        template <typename Func/*, typename ...Args*/>
        class FuncBench {
        public:
            using Ret = FuncReturn<Func/*, Args...*/>;

            template <typename ...Args>
            MeasureResult<Ret> run(Args&& ...args) {
                results_.push_back(func_bench(fut_, std::forward<Args>(args)...));
                return results_.back();
            }

            template <typename ...Args>
            void run_multiple(const size_t count, Args&& ...args) {
                results_.reserve(count);
                for (auto i = 0u; i < count; ++i)
                    results_.push_back(func_bench(fut_, std::forward<Args>(args)...));
            }

            size_t size() const { return results_.size(); }
            
            FuncBench(Func&& func) : fut_{ std::forward<Func>(func) } {}

        private:
            Func fut_;
            std::vector<MeasureResult<Ret>> results_;
        };

        template <typename Func>
        static FuncBench<Func> make_func_bench(Func&& func) {
            return FuncBench<Func>(std::forward<Func>(func));
        }

        template <typename T, typename Func>
        static FuncBench<Func> make_func_bench(T&& object, Func&& func) {
            return FuncBench<Func>([]() {std::forward<Func>(func); });
        }
    }
}
