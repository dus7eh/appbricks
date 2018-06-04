/*
* test_variant.cpp
*
*  Created on: May 17, 2018
*      Author: Dusteh
*/

#include <gtest/gtest.h>
#include <core/stringview.h>
using bricks::core::StringView;

TEST(StringViewTest, CreateView) {
    const std::string text{ "this is a test string" };
    const auto sv_whole1 = StringView{ text.begin(), text.end() };
    const auto sv_whole2 = StringView{ text };
    const auto sv_cut1 = StringView{ text.begin() + 10, text.end() };
    const auto sv_cut2 = StringView{ text.begin(), 4 };
    
    EXPECT_EQ(sv_whole1.as_string(), text.c_str());
    EXPECT_EQ(sv_cut1.as_string(), "test string");
    EXPECT_EQ(sv_cut2.as_string(), "this");
}

TEST(StringViewTest, UseIterators) {
    const std::string text{ "this is a test string!" };
    const auto sv_whole = StringView{ text.begin(), text.end() };
    const auto sv_sub = StringView{ sv_whole.begin() + 15, --sv_whole.end() };
    const auto sv_sub2 = StringView{ std::begin(sv_sub), std::end(sv_sub) - 3 };

    const std::string t2{ text.rbegin() + 1, text.rbegin() + 7 };

    EXPECT_EQ(sv_sub.as_string(), "string");
    EXPECT_EQ(sv_sub2.as_string(), "str");
}

TEST(StringViewTest, OperatorArray) {
    const std::string text{ "000abc000" };
    const auto sv_mid = StringView{ text.begin() + 3, text.end() - 3 };
    EXPECT_EQ(sv_mid[0], 'a');
    EXPECT_EQ(sv_mid[2], 'c');
    EXPECT_THROW(sv_mid[3], std::out_of_range);
    EXPECT_THROW(StringView(text.end(), text.begin()), std::range_error);
}

TEST(StringViewTest, SizeMethod) {
    const std::string text{ "000abc000" };
    const auto sv_mid = StringView{ text.begin() + 3, text.end() - 3 };
    EXPECT_EQ(sv_mid.size(), 3);
    EXPECT_EQ(sv_mid.empty(), false);

    const auto sv_none = StringView{ sv_mid.begin() + 3, sv_mid.end() };
    EXPECT_EQ(sv_none.size(), 0);
    EXPECT_EQ(sv_none.empty(), true);
}

TEST(StringViewTest, OperatorStream) {
    const std::string text{ "abcxyzabc" };
    const auto sv_mid = StringView{ text.begin() + 3, text.end() - 3 };
    std::stringstream str;
    str << sv_mid;

    EXPECT_EQ(str.str(), "xyz");
}

TEST(StringViewTest, CStr) {
    const std::string text{ "abcdef" };
    const auto sv_sub = StringView{ text.begin() + 2, 2 };
    const auto ptr = sv_sub.c_str();

    EXPECT_EQ(ptr, text.c_str() + 2);
}