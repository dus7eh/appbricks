/*
 * main.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Dusteh
 */

#include "core/variant.h"
#include "text/textutils.h"
#include "text/text.h"

#include <iostream>
#include <string>
int main()
{
	using dp::core::Variant;
	int k = 7;
	auto var = Variant{4};
	auto var2 = Variant{k};

	auto p = var2.get_as<int>();
	(void)p;

	char t1[] = "text with\twhitespaces\nand more";
	std::string s1 = t1;
	namespace tu = dp::textutils;
	//auto r1 = tu::remove_whitespaces(t1);
	auto r2 = tu::remove_whitespaces(s1);
	std::cout << r2 << std::endl;

	using dp::text::Text;
	Text t(s1);

	return 0;
}
