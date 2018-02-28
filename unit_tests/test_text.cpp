/*
 * test_text.cpp
 *
 *  Created on: Feb 1, 2018
 *      Author: Dusteh
 */

#include <gtest\gtest.h>
#include <text\text.h>

using dp::text::Text;

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

TEST(TextTest, TextMethodRemoveWhitespace)
{
   auto text = "a b c d e f";

   Text txt1 = text;
   auto txt2 = txt1.remove_whitespaces();
   EXPECT_EQ(txt1.as_string(), text);
   EXPECT_EQ(txt2.as_string(), "abcdef");
}

TEST(TextTest, TextMethodRevert)
{
   auto text = "a b c d e f";

   Text txt1 = text;
   auto txt2 = txt1.reverse();
   EXPECT_EQ(txt1.as_string(), text);
   EXPECT_EQ(txt2.as_string(), "f e d c b a");
}

TEST(TextTest, TextMethodSplit)
{
   auto text = "a b c d e f ";

   Text txt1 = text;
   auto txt1_arr = txt1.split(" ");
   auto txt2_arr = txt1.split();
}
