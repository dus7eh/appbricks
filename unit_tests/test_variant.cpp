/*
 * test_variant.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: Dusteh
 */

#include <gtest\gtest.h>

#include <vector>
#include <core\variant.h>

using dp::core::Variant;

TEST(VariantTest, VariantCreateExplicitType)
{
   // rvalues
   const auto var1 = Variant(5);
   const auto var2 = Variant(4.3);
   EXPECT_EQ(5, var1.get<int>());
   EXPECT_EQ(4.3, var2.get<double>());

   // lvalues
   const auto val_int = -3;
   const auto var3 = Variant(val_int);
   EXPECT_EQ(-3, var3.get<int>());

    // more lvalues
    const auto expected = std::vector<char>{ 2, 6, -9 };
    const auto var4 = Variant(expected);
    EXPECT_EQ(expected, var4.get<std::vector<char>>());
}

TEST(VariantTest, VariantCreateImplicitType)
{
   Variant var1 = 4;
   Variant var2 = 4.3;
   EXPECT_EQ(var1.get<int>(), 4);
   EXPECT_EQ(var2.get<double>(), 4.3);

   const auto expected = std::vector<char>{ 2, 6, -9 };
   Variant var3 = expected;
   EXPECT_EQ(var3.get<std::vector<char>>(), expected);
}

TEST(VariantTest, VariantGetUnconvertibleType)
{
   const auto value = Variant(4.5);
   EXPECT_THROW(value.get<int>(), std::bad_typeid);

    // TODO: consider the commented case
    // EXPECT_EQ(4, value.get_as<int>());
}

TEST(VariantTest, VariantTypeConversionExplicit)
{
   Variant var1 = -15;

    // TODO: implement
    // EXPECT_EQ(var1.get_as<long long>(), -15ll);
    // EXPECT_EQ(var1.get_as<bool>(), true);
    // EXPECT_EQ(var1.get_as<double>(), -15.0);
    // EXPECT_EQ(var1.get_as<uint32_t>(), uint32_t(-15));
    // EXPECT_EQ(var1.get_as<std::string>(), "-15");
}
