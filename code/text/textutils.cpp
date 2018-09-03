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
            if (maxHits < 0) {
                const auto pos = text.find_first_not_of(prefix);
                return pos == std::string::npos ? text : text.substr(pos);
            }

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
            if (maxHits < 0) {
                const auto pos = text.find_last_not_of(suffix);
                return pos == std::string::npos ? text : text.substr(0, pos + 1);
            }

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

        StringArray split(std::string text, std::string delim)
        {        
            StringArray res;
            auto pos = 0;
            while (pos = text.find_first_of(delim) != std::string::npos)
            {
                res.push_back(text.substr(0, pos));
                text.erase(0, pos + delim.size());
            }
            res.push_back(text);
            return res;
        }

        std::string join(const StringArray & text, std::string delim)
        {
            auto res = std::string{};
            for (const auto& item : text) {
                res += item + delim;
            }
            return remove_suffix(res, delim, 1);
        }
    }
}
