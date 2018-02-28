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
#include "textutils.h"

namespace dp
{
   namespace text
   {
      class Text
      {
      public:
         Text() = default;

         template <size_t s>
         Text(const char (&text)[s]): text_{text} {}
         Text(const char* text) : text_{text} {}
         Text(const std::string& text) : text_{text}{}
         Text(std::string&& text) : text_{std::move(text)}{}

         Text& operator=(const Text& text) = default;
         Text& operator+=(const Text& rhs) { text_ += rhs.text_; return *this; }

         std::string as_string() const { return text_; }
         std::string& as_string() { return text_; }

         // TODO: create from a type, tag dispatch for integral and floating
         template <typename T>
         static Text from(T&& value) { return {}; }

//       template <typename T = std::enable_if_t<std::is_integral<T>

         // convert to a type, tag dispatch for integral and floating
         template <typename T>
         std::string as() const { return {}; }

         // format a string filled with tokens
         template <typename T>
         Text& format(T&& value) { return {}; }

         // Member functions delegated to textutils function calls.
         // Return a reference to allow cascade method calling
         Text remove_whitespaces() { return textutils::remove_whitespaces(text_); }
         Text reverse() { auto text = text_; std::reverse(text.begin(), text.end()); return text; }
         auto split(std::string delimeter = "") { return textutils::split(text_, delimeter); }

      private:
         std::string text_;
      };

      Text operator+(Text& lhs, const Text& rhs)
      {
         lhs += rhs;
         return lhs;
      }
   }
   namespace detail_
   {
      struct integral_tag{};
      struct floating_tag{};
      struct string_tag{};
   }
}

#endif /* TEXT_H_ */
