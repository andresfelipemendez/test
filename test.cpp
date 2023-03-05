#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#define UNIT_TESTING
#include "main.cpp"

std::vector<std::vector<std::pair<std::string, std::string>>> processedInput {
    {
            /*0*/{"in",          "inee"      },
            /*1*/{"eedane",      "da"        },
            /*2*/{"xampl",       "nexamp"    },
            /*3*/{"es",          "les"       },
            /*4*/{"tri",         "tring"     },
            /*5*/{"ngt",         "tha"       },
            /*6*/{"ha",          "tha"       },
            /*7*/{"thas",        "smul"      },
            /*8*/{"mult",        "tiple"     },
            /*9*/{"ip",          "in"        },
            /*10*/{"leinputs",    "puts"      },
    },
    {
        /*00*/{ "inee",    "in"         },
        /*01*/{ "da",      "eedane"     },
        /*02*/{ "nexamp",  "xampl"      },
        /*03*/{ "les",     "es"         },
        /*04*/{ "tring",   "tri"        },
        /*05*/{ "tha",     "ngt"        },
        /*06*/{ "tha",     "ha"         },
        /*07*/{ "smul",    "thas"       },
        /*08*/{ "tiple",   "mult"       },
        /*09*/{ "in",      "ip"         },
        /*10*/{ "puts",   "leinputs"   },
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

TEST_CASE( "EmptyStateIsNotValidState", "[factorial]" ) {
    std::vector<int> state;
    REQUIRE( isValidState(state, processedInput[0]) == false );
}

TEST_CASE( "isValidState", "[factorial]" ) {
    {
        std::vector<int> state {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        REQUIRE( isValidState(state, processedInput[0]) == true );
    }
    {
        std::vector<int> state {4, 5, 6, 7, 8, 9, 10};
        REQUIRE( isValidState(state, processedInput[0]) == true );
    }
    {
        std::vector<int> state {4, 5, 6, 7, 8, 9, 10, 0};
        REQUIRE( isValidState(state, processedInput[0]) == false );
    }
}

TEST_CASE( "prune <", "[factorial]" ) {
    std::vector<int> state  {0} ;
    auto potentialCandidates = {1,2,3,4,5,6,7,8,9,10};
    auto pruned = prune(potentialCandidates, state, processedInput[0]);
    REQUIRE( pruned.size() == 1 );
    REQUIRE( pruned[0] == 1 );
}

TEST_CASE( "prune > ", "[factorial]" ) {
    std::vector<int> state  {0,1,2} ;
    auto potentialCandidates = {3,4,5,6,7,8,9,10};
    auto pruned = prune(potentialCandidates, state, processedInput[0]);
    REQUIRE( pruned.size() == 1 );
    REQUIRE( pruned[0] == 3 );
}

TEST_CASE( "prune in the middle ", "[factorial]" ) {
    std::vector<int> state  {4,5,6,7,8} ;
    auto potentialCandidates = {0,1,2,3,9,10};
    auto pruned = prune(potentialCandidates, state, processedInput[0]);
    REQUIRE( pruned.size() == 1 );
    REQUIRE( pruned[0] == 9 );
}

TEST_CASE( "prune in the middle flipped side", "[factorial]" ) {
    std::vector<int> state  {4,5,6,7,8} ;
    auto potentialCandidates = {0,1,2,3,9,10};
    auto pruned = prune(potentialCandidates, state, processedInput[1]);
    REQUIRE( pruned.size() == 1 );
    REQUIRE( pruned[0] == 9 );
}


TEST_CASE( "prune == ", "[factorial]" ) {
    std::vector<int> state  {0,1,2,3,} ;
    auto potentialCandidates = {4,5,6,7,8,9,10};
    auto pruned = prune(potentialCandidates, state, processedInput[0]);
    REQUIRE( pruned.size() == 1 );
    REQUIRE( pruned[0] == 4 );
}

TEST_CASE( "compareSubsetString", "[factorial]" ) {

    auto& firstPair = processedInput[0][0];
    REQUIRE( compareSubsetString(firstPair.first, firstPair.second) == true );

    auto& secondPair = processedInput[0][1];
    REQUIRE( compareSubsetString(secondPair.first, secondPair.second) == false );

    auto& fifthPair = processedInput[0][4];
    REQUIRE( compareSubsetString(fifthPair.first, fifthPair.second) == true );
}

TEST_CASE( "getCandidates", "[factorial]" ) {
    {
        std::vector<int> state;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 2 );
        REQUIRE( candidates[0] == 0 );
        REQUIRE( candidates[1] == 4 );
    }
    {
        std::vector<int> state  {0} ;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 1 );
        REQUIRE( candidates[0] == 1 );
    }
    {
        std::vector<int> state  {4} ;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 1 );
        REQUIRE( candidates[0] == 5 );
    }
    {
        std::vector<int> state  {4,5} ;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 1 );
        REQUIRE( candidates[0] == 6 );
    }
    {
        std::vector<int> state  {4,5,6,7,8} ;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 1 );
        //REQUIRE( candidates == 1 );
    }
    {
        std::vector<int> state  {4,5,6,7,8,9,10} ;
        auto candidates = getCandidates(state, processedInput[0]);
        REQUIRE( candidates.size() == 1 );
        //REQUIRE( candidates == 1 );
    }
}

//TEST_CASE( "serial search 0", "[factorial]" ) {
//    std::vector<int> state;
//    std::vector<std::vector<int>> solutions;
//    std::mutex solutions_mutex;
//    serialSearch(state, solutions, processedInput[0]);
//    REQUIRE( solutions.size() == 4 );
//    REQUIRE( solutions[0].size() == 4 );
//}

TEST_CASE( "async search 0", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[0], solutions_mutex);
    REQUIRE( solutions.size() == 4 );
    REQUIRE( solutions[0].size() == 4 );
    REQUIRE_THAT( solutions[0], Catch::Matchers::Equals(std::vector<int>{ 0, 1, 2, 3 }));
}

TEST_CASE( "async search 1", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[1], solutions_mutex);
    REQUIRE( solutions.size() == 4 );

}

TEST_CASE( "async search 2", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[2], solutions_mutex);
    REQUIRE( solutions.size() == 1 );
    REQUIRE( solutions[0].size() == 5 );
    REQUIRE_THAT( solutions[0], Catch::Matchers::Equals(std::vector<int>{ 4, 3, 2, 0, 1 }));
}

TEST_CASE( "async search 3", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[3], solutions_mutex);
    REQUIRE( solutions.size() == 1 );
    REQUIRE( solutions[0].size() == 7 );
    REQUIRE_THAT( solutions[0], Catch::Matchers::Equals(std::vector<int>{ 0, 6, 4, 7, 2, 3, 1 }));


}

TEST_CASE( "async search 4", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[4], solutions_mutex);
    REQUIRE( solutions.size() == 4 );

}

TEST_CASE( "async search 5", "[factorial]" ) {
    std::vector<int> state;
    std::vector<std::vector<int>> solutions;
    std::mutex solutions_mutex;
    search(state, solutions, processedInput[5], solutions_mutex);
    REQUIRE( solutions.size() == 0 );
}


TEST_CASE( "sort solutions", "[factorial]" ) {
    std::vector<std::string> a {
            "cd",
            "ab",
            "ad",
            "b",
            "bad",
            "a",
            "bac",
            "bc",
            "c",
            "ac",
            "adc",
            "abd",
    };

    std::sort(a.begin(), a.end(), [](auto a, auto b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    });
    std::stable_sort(a.begin(), a.end());
    REQUIRE( a[0].size() == 1 );
}
