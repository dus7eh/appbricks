/*
 * optional.h
 *
 *  Created on: Jun 05, 2018
 *      Author: Damian Ellwart
 */

#pragma once
#include <memory>
#include <exception>
#include "helpers.h"

namespace bricks
{
    namespace core
    {
        class BadAccess : public std::exception
        {
            virtual const char* what() const noexcept override {
                return "Incorrect object/value access";
            }
        };

        template <typename T>
        class Optional
        {
        public:
            Optional() noexcept = default;
            Optional(T&& arg) : data_{ make_unique<T>(std::forward<T>(arg)) } { }
            Optional(Optional<T>&& rhs) noexcept : data_{ std::move(rhs.data_) } { }
            Optional(const Optional<T>& rhs) {
                if (rhs)
                    data_ = make_unique<T>(*rhs);
            }

            ~Optional() = default;

            friend void swap(Optional<T>& lhs, Optional<T>& rhs) noexcept {
                std::swap(lhs.data_, rhs.data_);
            }

            const T& get() const {
                if (empty())
                    throw BadAccess();
                return *data_;
            }
            T& get() { return const_cast<T&>(static_cast<const Optional<T>&>(*this).get()); }

            T get_or_default(T&& dflt) {
                return empty() ? std::forward<T>(dflt) : get();
            }

            Optional<T>& operator=(Optional<T> rhs) noexcept {
                swap(*this, rhs);
                return *this;
            }

            bool empty() const noexcept { return data_ == nullptr; }
            
            explicit operator bool() const noexcept { return !empty(); }
            const T& operator *() const { return get(); }
            T& operator *() { return get(); }

            const T* operator->() const { return data_.get(); }
            T* operator->() { return data_.get(); }

        private:
            std::unique_ptr<T> data_;
        };

        template <typename T>
        Optional<T> make_optional(T&& arg) {
            return Optional<T>(std::forward<T>(arg));
        }
    }

    template<typename T>
    void swap(core::Optional<T>& lhs, core::Optional<T>& rhs) {
        swap(lhs, rhs);
    }
}
