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

using bricks::bench::FuncBench;
using bricks::bench::func_bench;
using bricks::bench::make_func_bench;

namespace {

    void task_empty() {}
    int task_sum(const std::vector<int>& data) {
        return std::accumulate(data.begin(), data.end(), 0);
    }
    double task_avg(const std::vector<int>& data, int init) {
        return std::accumulate(data.begin(), data.end(), init) / data.size();
    }

    int task_const() { return 5; }

    struct Members {
        int mul(int value) const noexcept { return value * data; }
    private:
        int data = 3;
    };
}

TEST(TimeMeasureTest, TimeMeasureSimpleStatic)
{
    auto meas_1 = func_bench(task_empty);

    auto data = std::vector<int>{ 1, 2, 3, 4};
    auto meas_2 = func_bench([&data]() { return task_sum(data); });

    EXPECT_TRUE(meas_1.time.count() > 0);
    EXPECT_TRUE(meas_2.time.count() > 0);
    EXPECT_EQ(meas_2.result.get(), 10);
}

TEST(TimeMeasureTest, TimeMeasureCallWithVarArgs)
{
    auto data = std::vector<int>{ 1, 2, 3 };
    auto meas_1 = func_bench(&task_sum, data);
    auto meas_2 = func_bench(&task_avg, data, 6);

    EXPECT_EQ(meas_1.result.get(), 6);
    EXPECT_EQ(meas_2.result.get(), 4);
}

TEST(TimeMeasureTest, TimeMeasureViaClassSingleRun)
{
    auto meas = make_func_bench(&task_empty);
    meas.run();
    meas.run();
    meas.run();
    meas.run();
    EXPECT_EQ(meas.size(), 4);
}

TEST(TimeMeasureTest, TimeMeasureViaClassMultiRun)
{
    auto meas = make_func_bench(&task_const);
    meas.run_multiple(20);
    EXPECT_EQ(meas.size(), 20);
}

TEST(TimeMeasureTest, TimeMeasureClassMember)
{
    Members memb{};
    auto ooo = &Members::mul;
    auto constexpr ccc = std::is_member_function_pointer<decltype(ooo)>::value;
    ((memb).*(ooo))(3);

    auto mmm = std::mem_fn(&Members::mul);
    mmm(&memb, 1);
    
    auto meas = make_func_bench(&memb, &Members::mul);
    /*auto res = meas.run(10);
    EXPECT_EQ(res.result, 30);*/
}