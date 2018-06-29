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
                virtual std::unique_ptr<Base> clone() const = 0;
                virtual ~Base() = default;
            private:
            };

            template <typename T>
            class Entity : public Base {
            public:
                Entity(T&& data) : data_{ std::forward<T>(data) } { }
                Entity(const Entity& data) = delete;

                typedef typename std::decay<T>::type type;

                bool is(id id) const override {
                    return typeid(T).hash_code() == id;
                }
                const T& get() const {
                    return data_;
                }
                T& get() {
                    return data_;
                }
                std::unique_ptr<Base> clone() const {
                    return bricks::make_unique<Entity<typename type>>(std::move(typename type(data_)));
                }

            private:
                typename type data_;
            };

            std::unique_ptr<Base> item_ = nullptr;

        public:
            Blob() = default;
            Blob(Blob &&rhs) : item_{ std::move(rhs.item_) } { }
            Blob(const Blob &rhs) : item_ { rhs.item_->clone()} { }

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

            bool empty() const noexcept {
                return !item_;
            }

            template <typename T>
            T get() const {
                if (!item_)
                    throw std::exception("This object is empty. Probably a value was moved from it.");
                if (!is<T>())
                    throw std::bad_typeid();
                return static_cast<Entity<T>*>(item_.get())->get();
            }
        };

    }
}
