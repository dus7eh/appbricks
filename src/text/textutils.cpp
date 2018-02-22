/*
 * textutils.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: Dusteh
 */

#include "textutils.h"
#include <algorithm>

namespace dp
{
	namespace textutils
	{
		std::string to_upper(std::string text);
		std::string to_lower(std::string text);

		std::string remove_whitespaces(std::string text)
		{
			text.erase(
				std::remove_if(text.begin(), text.end(), [](const auto& letter){
					return std::isspace(letter);
				}),
				text.end()
			);

			return text;
		}

		std::string replace(std::string text, std::string oldSeq, std::string newSeq);

		StringArray split(std::string text, std::string delim)
		{
		    return {};
		}

		std::string join(std::string delim);
	}
}
