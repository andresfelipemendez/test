#include <gtest/gtest.h>

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

TEST(processInput, SplittInputGroups) {
    auto processedInput = processInput(input);
    EXPECT_EQ(processedInput.size(), 5);
    EXPECT_EQ(processedInput[0].size(), 11);
}

TEST(processInput, SplittInputString) {
    auto processedInput = splitString("in inee", ' ');
    EXPECT_EQ(processedInput.size(), 2);
    EXPECT_EQ(processedInput[0], "in");
    EXPECT_EQ(processedInput[1], "inee");
}

TEST(solveEmilPuzzle, solveAllCases) {
    EXPECT_EQ(solveEmilPuzzle(input)[0], "hi");
}

TEST(solveEmilPuzzle, solveFirstCase) {
    auto pairGroup = processInput(input)[0];
    EXPECT_EQ(solve(pairGroup), "hi");
}

TEST(solveEmilPuzzle, solveSecondCase) {
    auto pairGroup = processInput(input)[1];
    EXPECT_EQ(solve(pairGroup), "dearalanhowareyou");
}

TEST(solveEmilPuzzle, getCandidates) {
    auto state = std::vector<int> {};
    auto listofpairs = std::vector<std::pair<std::string,std::string>> {
            /*0*/{"in", "inee"},
            /*1*/{"eedane", "da"},
            /*2*/{"xampl", "nexamp"},
            /*3*/{"es", "les"},
            /*4*/{"tri", "tringtha"},
            /*5*/{"ngtha", "tha"},
            /*6*/{"thas", "smu"},
            /*7*/{"mult", "tiple"},
            /*8*/{"ip", "in"},
            /*9*/{"leinpu", "puts"},
            /*10*/{"supto", "upto"},
    };
    auto candidates = getCandidates(state, listofpairs);
    EXPECT_EQ(candidates.size(), 2);
    EXPECT_EQ(candidates[0], 0);
    EXPECT_EQ(candidates[1], 4);
}

TEST(solveEmilPuzzle, compareSubsetString) {
    EXPECT_FALSE(compareSubsetString("ip", "in"));
    EXPECT_FALSE(compareSubsetString("xampl", " nexamp"));
}

TEST(solveEmilPuzzle, prune) {

}