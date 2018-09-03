/*
 * test_text.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: Damian Ellwart
 */

#include <gtest/gtest.h>
#include <text/text.h>

using bricks::text::Text;

TEST(TextTest, TextCreateAndReadObject)
{
    Text txt1;
    Text txt2("abc");
    Text txt3{"def"};

    const std::string message = "this is some message";
    Text txt4(message);
    auto txt5 = Text(message);

    EXPECT_EQ(txt1.as_string(), "");
    EXPECT_EQ(txt2.as_string(), "abc");
    EXPECT_EQ(txt3.as_string(), "def");
    EXPECT_EQ(txt4.as_string(), message);
    EXPECT_EQ(txt5.as_string(), message);
}

TEST(TextTest, TextAssignOperator)
{
    Text txt1;
    txt1 = "abc";

    const std::string message = "this is some message";
    Text txt2;
    txt2 = message;

    EXPECT_EQ(txt1.as_string(), "abc");
    EXPECT_EQ(txt2.as_string(), message);

    const std::string shortMessage = "short message";
    txt2 = shortMessage;
    EXPECT_EQ(txt2.as_string(), shortMessage);
}

TEST(TextTest, TextCreateSpecialization)
{
    auto txtInt = Text::from(5);
    EXPECT_EQ(txtInt.as_string(), "5");

    auto txtDbl = Text::from(6.7);
    EXPECT_EQ(txtDbl.as_string(), "6.7");

    auto txtNeg = Text::from(-7);
    EXPECT_EQ(txtNeg.as_string(), "-7");
}

TEST(TextTest, TextConversion)
{
    EXPECT_EQ(Text("5").as<int>(), 5);
    EXPECT_EQ(Text("2.4").as<double>(), 2.4);
    EXPECT_EQ(Text("-7").as<int>(), -7);
}

TEST(TextTest, TextMethodRemoveWhitespace)
{
    auto text = "a b c d e f";

    Text txt1 = text;
    auto txt2 = txt1.remove_whitespaces();
    EXPECT_EQ(txt1.as_string(), text);
    EXPECT_EQ(txt2.as_string(), "abcdef");
}

TEST(TextTest, TextMethodRemovePrefix)
{
    auto text = "abcabcTEST";

    Text txt = text;
    EXPECT_EQ(txt.remove_prefix("a").as_string(), "bcabcTEST");
    EXPECT_EQ(txt.remove_prefix("abc").as_string(), "TEST");
    EXPECT_EQ(txt.remove_prefix("abc", 1).as_string(), "abcTEST");
    EXPECT_EQ(txt.remove_prefix("abc", 10).as_string(), "TEST");

    EXPECT_EQ(txt.remove_prefix("T").as_string(), text);
    EXPECT_EQ(txt.remove_prefix("TEST", 10).as_string(), text);

    EXPECT_EQ(Text().remove_prefix("TEST").as_string(), "");
    EXPECT_EQ(Text().remove_prefix("TEST", 10).as_string(), "");
}

TEST(TextTest, TextMethodRemoveSuffix)
{
    auto text = "TESTxyzxyz";

    Text txt = text;
    EXPECT_EQ(txt.remove_suffix("z").as_string(), "TESTxyzxy");
    EXPECT_EQ(txt.remove_suffix("xyz").as_string(), "TEST");
    EXPECT_EQ(txt.remove_suffix("xyz", 1).as_string(), "TESTxyz");
    EXPECT_EQ(txt.remove_suffix("xyz", 10).as_string(), "TEST");
    
    EXPECT_EQ(txt.remove_suffix("T").as_string(), text);
    EXPECT_EQ(txt.remove_suffix("TEST", 10).as_string(), text);
    
    EXPECT_EQ(Text().remove_suffix("TEST").as_string(), "");
    EXPECT_EQ(Text().remove_suffix("TEST", 10).as_string(), "");
}

TEST(TextTest, TextMethodSplit)
{
    using bricks::text::StringArray;
    const auto expected_simple = StringArray{ "a", "b", "c", "d" };
    const auto expected_complex = StringArray{ "a", "b", "c", "d", "" };

    const auto text_simple = Text("a;b;c;d");
    const auto text_complex = Text("a=>b=>c=>d=>");

    auto res = text_simple.split(";");
    EXPECT_TRUE(expected_simple.size() == res.size() && std::equal(res.begin(), res.end(), expected_simple.begin()));

    res = text_complex.split("=>");
    EXPECT_TRUE(expected_complex.size() == res.size() && std::equal(res.begin(), res.end(), expected_complex.begin()));
}

TEST(TextTest, TextMethodJoin)
{
    using bricks::text::StringArray;
    const auto expected_simple = "a;b;c;d";
    const auto expected_complex = "a=>b=>c=>d=>";
    
    const auto data_simple = StringArray{ "a", "b", "c", "d" };
    const auto data_complex = StringArray{ "a", "b", "c", "d", "" };

    auto res = Text::join(data_simple, ";");
    EXPECT_EQ(res, expected_simple);

    res = Text::join(data_complex, "=>");
    EXPECT_EQ(res, expected_complex);
}

TEST(TextTest, TextMethodRevert)
{
    auto text = "a b c d e f";

    Text txt1 = text;
    auto txt2 = txt1.reverse();
    EXPECT_EQ(txt1.as_string(), text);
    EXPECT_EQ(txt2.as_string(), "f e d c b a");
}
