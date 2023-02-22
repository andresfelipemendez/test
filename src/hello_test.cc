#include <gtest/gtest.h>

#include "backtrack.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest1, BasicAssertions) {
    EXPECT_EQ(backTrack("_"), "hi");
}