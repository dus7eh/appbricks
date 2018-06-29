/*
 * blob.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Damian Ellwart
 */

#pragma once

#include <string>
#include <typeinfo>
#include <memory>
#include <type_traits>
#include "helpers.h"

namespace bricks {
    namespace core {
        class Blob {
            using id = size_t;

            class Base {
            public:
                virtual bool is(id) const = 0;
                virtual ~Base() = default;
            private:
            };

            template <typename T>
            class Entity : public Base {
            public:
                Entity(T&& data) : data_{ std::forward<T>(data) } { }
                Entity(const Entity& data) = delete;

                bool is(size_t id) const override {
                    return typeid(T).hash_code() == id;
                }
                const T& get() const {
                    return data_;
                }
                T& get() {
                    return data_;
                }

            private:
                typename std::decay<T>::type data_;
            };

            std::unique_ptr<Base> item_ = nullptr;

        public:
            Blob(Blob &&rhs) : item_{ std::move(rhs.item_) } { }
            /*Blob(const Blob &rhs) {
                // TODO: implement
            }*/

            template <typename T, typename = enable_if_t<!std::is_same<typename std::decay<T>::type, Blob>::value>>
            Blob(T&& data) : item_{ bricks::make_unique<Entity<T>>(std::forward<T>(data)) } { }

            friend void swap(Blob& lhs, Blob& rhs) noexcept {
                std::swap(lhs.item_, rhs.item_);
            }

            Blob &operator=(Blob rhs) noexcept {
                swap(*this, rhs);
                return *this;
            }

            template <typename T>
            bool is() const {
                return item_->is(typeid(T).hash_code());
            }

            template <typename T>
            T get() const {
                if (!is<T>())
                    throw std::bad_typeid();
                return static_cast<Entity<T>*>(item_.get())->get();
            }

            //template <typename T>
            //T get_as() const {
            //    // no checks done here
            //    const auto ptr = static_cast<Entity<T>*>(item_.get());
            //    return T(ptr->get());
            //}
        };

    }
}
