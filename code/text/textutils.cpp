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
        
        std::string remove_prefix(std::string text, std::string prefix, int maxHits)
        {
            if (maxHits < 0)
                return text.substr(text.find_first_not_of(prefix));
            
            while (maxHits > 0 &&
                   text.size() >= prefix.size() &&
                   std::equal(prefix.begin(), prefix.end(), text.begin())) {
                --maxHits;
                text = text.erase(0, prefix.size());
            }
            return text;
        }

        std::string remove_suffix(std::string text, std::string suffix, int maxHits)
        {
            if (maxHits < 0)
                return text.substr(0, text.find_last_not_of(suffix) + 1);

            while (maxHits > 0 &&
                   text.size() >= suffix.size() &&
                   std::equal(suffix.rbegin(), suffix.rend(), text.rbegin())) {
                --maxHits;
                text.erase((text.rbegin() + suffix.size()).base(), text.rbegin().base());
            }
            return text;
        }


        std::string remove_whitespaces(std::string text)
        {
            text.erase(
                std::remove_if(text.begin(), text.end(), [](const char& letter)
            {
                return std::isspace(letter);
            }),
            text.end()
            );

            return text;
        }

        std::string replace(std::string text, std::string oldSeq, std::string newSeq)
        {
            text.replace("abc", "def");
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
