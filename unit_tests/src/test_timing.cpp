/*
 * test_timing.cpp
 *
 *  Created on: Dec 02, 2018
 *      Author: Damian Ellwart
 */

#include <gtest/gtest.h>
#include <numeric>
#include <vector>
#include <core/timing.h>

using bricks::core::TimeMeasure;

void task_empty() {}
int task_sum(const std::vector<int>& data) {
    return std::accumulate(data.begin(), data.end(), 0);
}
double task_avg(const std::vector<int>& data, int init) {
    return std::accumulate(data.begin(), data.end(), init) / data.size();
}

TEST(TimeMeasureTest, TimeMeasureSimpleStatic)
{
    auto meas_1 = TimeMeasure::measure(task_empty);

    auto data = std::vector<int>{ 1, 2, 3, 4};
    auto meas_2 = TimeMeasure::measure([&data]() { return task_sum(data); });

    EXPECT_TRUE(meas_1.time.count() > 0);
    EXPECT_TRUE(meas_2.time.count() > 0);
    EXPECT_EQ(meas_2.result.get(), 10);
}

TEST(TimeMeasureTest, TimeMeatureCallWithVarArgs)
{
    auto data = std::vector<int>{ 1, 2, 3 };
    auto meas_1 = TimeMeasure::measure(&task_sum, data);
    auto meas_2 = TimeMeasure::measure(&task_avg, data, 6);

    EXPECT_EQ(meas_1.result.get(), 6);
    EXPECT_EQ(meas_2.result.get(), 4);
}