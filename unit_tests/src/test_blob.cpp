/*
 * test_blob.cpp
 *
 *  Created on: Jan 31, 2018
 *      Author: Damian Ellwart
 */

#include <gtest/gtest.h>

#include <vector>
#include <core/blob.h>

using bricks::core::Blob;

TEST(BlobTest, BlobCreateExplicitType)
{
    // rvalues
    const auto var1 = Blob(5);
    const auto var2 = Blob(4.3);
    EXPECT_EQ(5, var1.get<int>());
    EXPECT_EQ(4.3, var2.get<double>());

    // lvalues
    const auto val_int = -3;
    const auto var3 = Blob(val_int);
    EXPECT_EQ(-3, var3.get<int>());

    // more lvalues
    const auto expected = std::vector<char> { 2, 6, -9 };
    const auto var4 = Blob(expected);
    EXPECT_EQ(expected, var4.get<std::vector<char>>());
}

TEST(BlobTest, BlobCreateImplicitType)
{
    Blob var1 = 4;
    Blob var2 = 4.3;
    EXPECT_EQ(var1.get<int>(), 4);
    EXPECT_EQ(var2.get<double>(), 4.3);

    const auto expected = std::vector<char> { 2, 6, -9 };
    Blob var3 = expected;
    EXPECT_EQ(var3.get<std::vector<char>>(), expected);
}

TEST(BlobTest, BlobGetUnconvertibleType)
{
    const auto value = Blob(4.5);
    EXPECT_THROW(value.get<int>(), std::bad_typeid);
}

TEST(BlobTest, BlobConstructors)
{
    auto var1 = Blob(5.5);
    auto var2 = var1;

    EXPECT_EQ(var1.get<double>(), 5.5);
    EXPECT_EQ(var2.get<double>(), 5.5);

    auto var3 = std::move(var1);
    EXPECT_THROW(var1.get<double>(), std::exception);
    EXPECT_EQ(var1.empty(), true);
    EXPECT_EQ(var3.get<double>(), 5.5);
}

TEST(BlobTest, BlobEmpty)
{
    auto var1 = Blob();
    EXPECT_EQ(var1.empty(), true);
    EXPECT_THROW(var1.get<int>(), std::exception);
}

TEST(BlobTest, BlobSwap)
{
    auto var1 = Blob(12);
    auto var2 = Blob(3.3);

    swap(var1, var2);
    EXPECT_EQ(var1.get<double>(), 3.3);
    EXPECT_EQ(var2.get<int>(), 12);
}

TEST(BlobTest, BlobAssign)
{
    auto var1 = Blob();
    auto var2 = Blob(13);

    var1 = var2;
    var2 = 15;
    EXPECT_EQ(var1.get<int>(), 13);
    EXPECT_EQ(var2.get<int>(), 15);
}