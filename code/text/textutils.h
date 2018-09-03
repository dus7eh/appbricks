/*
 * textutil.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Damian Ellwart
 */

#ifndef TEXTUTILS_H_
#define TEXTUTILS_H_

#include <string>
#include <vector>
#include <algorithm>

namespace bricks {
    namespace text {
        std::string to_upper(std::string text);
        std::string to_lower(std::string text);

        /**
        * Trims all the specified chars in passed text from left to right until a character not defined in chars is encountered.
        */
        inline std::string trim_left(std::string text, std::initializer_list<char> chars) {
            const auto it = std::find_if_not(text.begin(), text.end(), [&chars](const auto& ch) {
                return std::find(std::begin(chars), std::end(chars), ch) == std::end(chars);
            });

            return{ it, text.end() };
        }
        inline std::string trim_left(std::string text, char ch) {
            return trim_left(text, { ch });
        }
        
        /**
        * Trims all the specified chars in passed text from right to left until a character not defined in chars is encountered.
        */
        inline std::string trim_right(std::string text, std::initializer_list<char> chars) {
            const auto rit = std::find_if(text.rbegin(), text.rend(), [&chars](const auto& ch) {
                return std::find(std::begin(chars), std::end(chars), ch) == std::end(chars);
            });

            return{ text.begin(), rit.base()};
        }
        inline std::string trim_right(std::string text, char ch) {
            return trim_right(text, { ch });
        }

        /**
        * Removes a prefix from the passed string. For maxHits=-1 this is done for all prefix occurrences or according to the maxHits value.  
        */
        std::string remove_prefix(std::string text, std::string prefix, int maxHits);
        
        /**
        * Removes a suffix from the passed string. For maxHits=-1 this is done for all suffix occurrences or according to the maxHits value.
        */
        std::string remove_suffix(std::string text, std::string suffix, int maxHits);

        /**
        * Removes whitespaces from the passed text.
        */
        std::string remove_whitespaces(std::string text);

        /**
        * Replaces oldSeq occurences in text with a new sequence defined in newSeq.
        */
        std::string replace(std::string text, std::string oldSeq, std::string newSeq);

        using StringArray = std::vector<std::string>;
        /**
        * Splits text according to the specified delimeter. As a result a non empty collection of strings is returned.
        */
        StringArray split(std::string text, std::string delim);

        /**
        * Joins a collection of strings by a specified delimeter. As a result single string value is returned.
        */
        std::string join(const StringArray& text, std::string delim);
    }
}


#endif /* TEXTUTILS_H_ */
