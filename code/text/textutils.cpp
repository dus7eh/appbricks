/*
 * textutils.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: Damian Ellwart
 */

#include "textutils.h"
#include <algorithm>
#include <cctype>

namespace bricks
{
    namespace text
    {
        std::string to_upper(std::string text)
        {
            std::transform(text.begin(), text.end(), text.begin(), ::toupper);
            return text;
        }

        std::string to_lower(std::string text)
        {
            std::transform(text.begin(), text.end(), text.begin(), ::tolower);
            return text;
        }

        std::string trim_left(std::string text, std::string chars)
        {
            // TODO: implement
            return {};
        }

        std::string trim_right(std::string text, std::string chars)
        {
            // TODO: implement
            return {};
        }

        std::string remove_prefix(std::string text, std::string prefix, int maxHits)
        {
            // TODO: implement
            return {};
        }

        std::string remove_suffix(std::string text, std::string suffix, int maxHits)
        {
            // TODO: implement
            return {};
        }


        std::string remove_whitespaces(std::string text)
        {
            text.erase(
                std::remove_if(text.begin(), text.end(), [](const auto& letter)
            {
                return std::isspace(letter);
            }),
            text.end()
            );

            return text;
        }

        std::string replace(std::string text, std::string oldSeq, std::string newSeq)
        {
            // TODO: implement
            return {};
        }

        StringArray split(std::string text, std::string delim)
        {
            // TODO: implement
            return{};
        }

        std::string join(const StringArray & text, std::string delim)
        {
            // TODO: implement
            return{};
        }
    }
}
