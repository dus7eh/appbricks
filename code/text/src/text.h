/*
 * text.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Dusteh
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <type_traits>
#include <string>
#include <algorithm>
#include "textutils.h"

namespace bricks
{
    namespace text
    {
        class Text
        {
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

            // TODO: create from a type, tag dispatch for integral and floating
            template <typename T>
            static Text from(T&& value)
            {
                return {};
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
            Text reverse()
            {
                auto text = text_;
                std::reverse(text.begin(), text.end());
                return text;
            }
            auto split(std::string delimeter = "")
            {
                return text::split(text_, delimeter);
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

#endif /* TEXT_H_ */
