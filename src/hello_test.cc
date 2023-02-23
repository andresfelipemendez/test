#include <gtest/gtest.h>

#include "backtrack.h"

TEST(HelloTest1, BasicAssertions) {
    std::string input = R"(5
are yo
you u
how nhoware
alan arala
dear de
8
i ie
ing ding
resp orres
ond pon
oyc y
hello hi
enj njo
or c
3
efgh efgh
d cd
abc ab
3
a ab
b bb
c cc
)";
    EXPECT_EQ(solveEmilPuzzle(input)[0], "hi");
}