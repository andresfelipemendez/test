//
// Created by Andres on 4/03/23.
//

#ifndef HELLO_TEST_EMIL_H
#define HELLO_TEST_EMIL_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <set>
#include <mutex>
#include <thread>
#include <future>

struct State {
    std::vector<int> current;
};

using ListOfPairs = std::vector<std::pair<std::string, std::string>>;

std::pair<std::string, std::string> splitString(const std::string& input, char delimiter);

bool isValidState(const State& state, const ListOfPairs& listOfPairs);

std::set<int> prune(const std::set<int>& potentialCandidates, State& state, const ListOfPairs& listOfPairs);

bool compareSubsetString(const std::string& first, const std::string& second);

std::set<int> getCandidates(State& state, const ListOfPairs& listOfPairs);

void search(State state, std::vector<State>& solutions, const ListOfPairs& listOfPairs, std::mutex& solutions_mutex);

std::string solve(const ListOfPairs& listOfPairs);

std::vector<std::string> solveEmilPuzzle(const std::vector<std::vector<std::pair<std::string, std::string>>>& processedInput);

#endif //HELLO_TEST_EMIL_H
