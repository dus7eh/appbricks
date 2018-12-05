/*
 * test_optional.cpp
 *
 *  Created on: Jun 05, 2018
 *      Author: Damian Ellwart
 */

#include <gtest/gtest.h>
#include <core/optional.h>

using bricks::core::Optional;

TEST(OptionalTest, OptionalReadData)
{
    Optional<double> value = 3.4;
    EXPECT_EQ(*value, 3.4);
    EXPECT_EQ(value.get(), 3.4);
}

TEST(OptionalTest, OptionalReadAndThrow)
{
    struct Dummy {
        int age = 3;
    };

    Optional<Dummy> empty{};
    EXPECT_THROW(*empty, bricks::core::BadAccess);
    EXPECT_DEATH(const int value = empty->age, "");
}

TEST(OptionalTest, OptionalReadOrDefault)
{
    Optional<int> empty;
    EXPECT_EQ(empty.get_or_default(3), 3);

    Optional<int> filled = Optional<int>(9);
    EXPECT_EQ(filled.get_or_default(2), 9);
}

TEST(OptionalTest, OptionalCopyCtor)
{
    Optional<double> value = 3.4;
    auto copy = value;
    EXPECT_EQ(*value, 3.4);
    EXPECT_EQ(*copy, 3.4);
    EXPECT_EQ(*value, *copy);
}

TEST(OptionalTest, OptionalMoveCtor)
{
    Optional<double> value = 5.9;
    Optional<double> copy = std::move(value);

    EXPECT_EQ(value.empty(), true);
    EXPECT_EQ(*copy, 5.9);
}

TEST(OptionalTest, OptionalCopyAssign)
{
    Optional<double> value = 3.4;
    Optional<double> assign;
    assign = value;
    EXPECT_EQ(*value, 3.4);
    EXPECT_EQ(*assign, 3.4);
    EXPECT_EQ(*value, *assign);
}

TEST(OptionalTest, OptionalMoveAssign)
{
    Optional<double> value = 3.4;
    Optional<double> assign;
    assign = std::move(value);
    EXPECT_EQ(value.empty(), true);
    EXPECT_EQ(*assign, 3.4);
}

TEST(OptionalTest, OptionalMake)
{
    using bricks::core::make_optional;

    const auto value = make_optional<int>(15);
    EXPECT_EQ(*value, 15);
}

TEST(OptionalTest, OptionalSwap)
{
    Optional<double> value1 = 1.2;
    Optional<double> value2 = 3.4;
    swap(value1, value2);
    EXPECT_EQ(*value1, 3.4);
    EXPECT_EQ(*value2, 1.2);

    bricks::swap(value1, value2);
    EXPECT_EQ(*value1, 1.2);
    EXPECT_EQ(*value2, 3.4);
}

TEST(OptionalTest, OptionalBoolOperator)
{
    Optional<int> empty;
    EXPECT_EQ(bool(empty), false);
    EXPECT_EQ(empty.empty(), true);

    Optional<int> filled = 5;
    EXPECT_EQ(bool(filled), true);

    Optional<int> empty_ptr;
    EXPECT_EQ(bool(empty_ptr), false);

    Optional<char*> filled_ptr = nullptr;
    EXPECT_EQ(bool(filled_ptr), true);
}

TEST(OptionalTest, OptionalPtrAccess)
{
    struct Dummy {
        std::string name = "abc";
        int value = 29;
    };

    const auto dummy = Optional<Dummy>(Dummy());
    EXPECT_EQ(dummy->name, "abc");
    EXPECT_EQ(dummy->value, 29);
}