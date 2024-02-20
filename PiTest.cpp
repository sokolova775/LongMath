#include "pi.h"
#include "gtest/gtest.h"
#include "time.h"

TEST(PI, PI100){
    clock_t start, finish;
    start = clock();
    auto _pi = PI::pi(100);
    finish = clock();
    EXPECT_EQ(PI::PI.toString(100), _pi.toString(100));
    EXPECT_GE(1, static_cast<double>(finish - start)/CLOCKS_PER_SEC);
}

TEST(PI, PI200){
    auto _pi = PI::pi(200);
    EXPECT_EQ(PI::PI.toString(200), _pi.toString(200));
}