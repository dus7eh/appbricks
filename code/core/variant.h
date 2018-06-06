/*
 * variant.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Dusteh
 */

#pragma once

#include <string>
#include <typeinfo>
#include <memory>
#include <type_traits>

namespace bricks
{
    namespace core
    {
        class Variant
        {
            using id = size_t;

            class Base
            {
            public:
                virtual bool is(id) const = 0;
                virtual ~Base() = default;
            private:
            };

            template <typename T>
            class Entity : public Base
            {
            public:
                Entity(T&& data) : data_{ std::forward<T>(data) } { }
                Entity(const Entity& data) = delete;

                bool is(size_t id) const override
                {
                    return typeid(T).hash_code() == id;
                }
                const T& get() const
                {
                    return data_;
                }
                T& get()
                {
                    return data_;
                }

            private:
                typename std::decay<T>::type data_;
            };

            std::unique_ptr<Base> item_ = nullptr;

        public:
            Variant(Variant &&rhs)
            {
                // TODO: implement
            }
            Variant(const Variant &rhs)
            {
                // TODO: implement
            }

            template <typename T, typename = std::enable_if_t<!std::is_same<typename std::decay<T>::type, Variant>::value>>
            Variant(T&& data) : item_{ std::make_unique<Entity<T>>(std::forward<T>(data)) } { }

            Variant &operator=(Variant s)
            {
                // TODO: implement
                return *this;
            }

            template <typename T>
            bool is() const
            {
                return item_->is(typeid(T).hash_code());
            }

            template <typename T>
            T get() const
            {
                if (!is<T>())
                    throw std::bad_typeid();
                return get_as<T>();
            }

            template <typename T>
            T get_as() const
            {
                auto ptr = static_cast<Entity<T>*>(item_.get());
                return ptr->get();
            }
        };

    }
}
