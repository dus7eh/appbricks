/*
 * textutil.h
 *
 *  Created on: Jan 31, 2018
 *      Author: Dusteh
 */

#ifndef TEXTUTILS_H_
#define TEXTUTILS_H_

#include <string>
#include <vector>

namespace dp
{
	namespace textutils
	{
		std::string to_upper(std::string text);
		std::string to_lower(std::string text);

		std::string trim_left(std::string text, std::string chars = " ");
		std::string trim_right(std::string text, std::string chars = " ");

		std::string remove_prefix(std::string text, std::string prefix, int maxHits = 1);
		std::string remove_suffix(std::string text, std::string suffix, int maxHits = 1);

		std::string remove_whitespaces(std::string text);
		std::string replace(std::string text, std::string oldSeq, std::string newSeq);

		using StringArray = std::vector<std::string>;
		StringArray split(std::string text, std::string delim);
		std::string join(const StringArray& text, std::string delim);
	}
}


#endif /* TEXTUTILS_H_ */
