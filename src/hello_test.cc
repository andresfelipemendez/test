#include <gtest/gtest.h>
#define UNIT_TEST
#include "backtrack.h"

std::string input = R"(11
in inee
eedane da
xampl nexamp
es les
tri tringtha
ngtha tha
thas smu
mult tiple
ip in
leinpu puts
supto upto
5
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

std::vector<std::vector<std::pair<std::string, std::string>>> processedInput
{
        {
                {"in", "inee"},
                {"eedane", "da"},
                {"xampl", "nexamp"},
                {"es", "les"},
                {"tri", "tringtha"},
                {"ngtha", "tha"},
                {"thas", "smu"},
                {"mult", "tiple"},
                {"ip", "in"},
                {"leinpu", "puts"},
                {"supto", "upto"},
        },
        {
                {"are", "yo"},
                {"you", "u"},
                {"how", "nhoware"},
                {"alan", "arala"},
                {"dear", "de"},
        },
        {
                {"i", "ie"},
                {"ing", "ding"},
                {"resp", "orres"},
                {"ond", "pon"},
                {"oyc", "y"},
                {"hello", "hi"},
                {"enj", "njo"},
                {"or", "c"},
        },
        {
                {"efgh", "efgh"},
                {"d", "cd"},
                {"abc", "ab"},
        },
        {
                {"a", "ab"},
                {"b", "bb"},
                {"c", "cc"},
        }
};

//TEST(solveEmilPuzzle, solveAllCases) {
//
//    EXPECT_EQ(solveEmilPuzzle(processedInput)[0], "hi");
//}
//
//TEST(solveEmilPuzzle, solveFirstCase) {
//
//    EXPECT_EQ(solve(processedInput[0]), "hi");
//}
//
//TEST(solveEmilPuzzle, solveSecondCase) {
//
//    EXPECT_EQ(solve(processedInput[0]), "dearalanhowareyou");
//}

//TEST(solveEmilPuzzle, getCandidates) {
//    State state;
//
//    auto candidates = getCandidates(state, listofpairs);
//    EXPECT_EQ(candidates.size(), 2);
//    EXPECT_EQ(candidates.count(0), 1);
//    EXPECT_EQ(candidates.count(4), 1);
//}

TEST(solveEmilPuzzle, compareSubsetString) {
    EXPECT_FALSE(compareSubsetString("ip", "in"));
    EXPECT_FALSE(compareSubsetString("xampl", " nexamp"));
}
//
//TEST(solveEmilPuzzle, prune) {
//
//}