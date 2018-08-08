/*
 * text.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Damian Ellwart
 */

#ifndef TEXT_H
#define TEXT_H

#include <type_traits>
#include <string>
#include <algorithm>
#include "textutils.h"
#include "helpers.h"

namespace bricks {
    namespace text {
        namespace detail_ {
            template <typename T, typename = void_t<>>
            struct to_string_spec_exists : std::false_type {};

            template <typename T>
            struct to_string_spec_exists<T, void_t<decltype(std::to_string(std::declval<T>()))>> : std::true_type {};
        }

        class Text {
        public:
            Text() = default;
            Text(Text&& text) = default;
            Text(const Text& text) = default;

            template <size_t s>
            Text(const char (&text)[s]): text_{text} {}
            Text(const char* text) : text_{text} {}
            Text(const std::string& text) : text_{text} {}
            Text(std::string&& text) : text_{std::move(text)} {}

            Text& operator=(const Text& text) = default;
            Text& operator=(Text&& text) = default;
            Text& operator+=(const Text& rhs)
            {
                text_ += rhs.text_;
                return *this;
            }

            std::string as_string() const
            {
                return text_;
            }
            std::string& as_string()
            {
                return text_;
            }

            template <typename T>
            static enable_if_t<std::is_integral<T>::value, Text> from(T&& value)
            {
                return std::to_string(std::forward<T>(value));
            }

            template <typename T>
            static enable_if_t<std::is_floating_point<T>::value, Text> from(T&& value)
            {
                return trim_right(std::to_string(value), '0');
            }

            // convert to a type, tag dispatch for integral and floating
            template <typename T>
            std::string as() const
            {
                return {};
            }

            // format a string filled with tokens
            template <typename T>
            Text& format(T&& value)
            {
                return {};
            }

            // Member functions delegated to textutils function calls.
            Text remove_whitespaces()
            {
                return text::remove_whitespaces(text_);
            }

            Text remove_prefix(std::string prefix, int maxHits = -1)
            {
                return text::remove_prefix(text_, prefix, maxHits);
            }

            Text remove_suffix(std::string suffix, int maxHits = -1)
            {
                return text::remove_suffix(text_, suffix, maxHits);
            }

            Text reverse()
            {
                auto text = text_;
                std::reverse(text.begin(), text.end());
                return text;
            }

            StringArray split(std::string delimeter = "") const
            {
                return text::split(text_, delimeter);
            }

            static std::string join(const StringArray& text_arr, std::string delimeter = "")
            {
                return text::join(text_arr, delimeter);
            }

        private:
            std::string text_;
        };

        inline Text operator+(Text& lhs, const Text& rhs)
        {
            lhs += rhs;
            return lhs;
        }
    }
}

#endif /* TEXT_H */
