#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <vector>
#include <mutex>
#include <thread>
#include <future>

enum class SearchSide {
    first,
    second,
    both,
    neither
};

using ListOfPairs = std::vector<std::pair<std::string, std::string>>;

std::pair<std::string, std::string> splitString(const std::string& input, char delimiter) {
    auto pos = input.find(delimiter);
    auto first = input.substr(0, pos);
    auto second = input.substr(pos + 1, input.size() - 1);
    return { first, second };
}

bool isValidState(const std::vector<int>& state, const ListOfPairs& listOfPairs) {
    std::string concatenatedLeft, concatenatedRight;
    for (const int index : state) {
        concatenatedLeft += listOfPairs[index].first;
        concatenatedRight += listOfPairs[index].second;
    }
    bool areEqual = concatenatedLeft == concatenatedRight;
    bool areNotEmpty = !concatenatedLeft.empty() || !concatenatedRight.empty();
    return areEqual && areNotEmpty;
}

bool compareSubsetString(const std::string& first,const std::string& second) {
    if (first.size() == second.size())
        return first == second;

    std::string overlappingOppositeSubstring;
    if(first.size() < second.size()){
        overlappingOppositeSubstring = second.substr(0, first.size());
        return overlappingOppositeSubstring == first;
    }
    else {
        overlappingOppositeSubstring = first.substr(0, second.size());
        return overlappingOppositeSubstring == second;
    }
}

std::vector<int> prune(const std::vector<int>& potentialCandidates, std::vector<int>& state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;
    std::string first, second;
    for (int pairIndex : state) {
        first += listOfPairs[pairIndex].first;
        second += listOfPairs[pairIndex].second;
    }

    std::string overlappingSubstring;
    SearchSide searchSide = SearchSide::neither;

    if (first.size() < second.size()) {
        overlappingSubstring = second.substr(first.size(), second.size() - first.size());
        searchSide = SearchSide::first;
    }
    else if (first.size() > second.size()) {
        overlappingSubstring = first.substr(second.size(), first.size() - second.size());
        searchSide = SearchSide::second;
    }
    else if (first.size() == second.size()) {
        searchSide = SearchSide::both;
    }

    for (int potentialCandidate : potentialCandidates) {
        auto pair = listOfPairs[potentialCandidate];
        switch (searchSide) {
            case SearchSide::first: {
                if(compareSubsetString(pair.first, overlappingSubstring))
                    candidates.push_back(potentialCandidate);
            }
                break;
            case SearchSide::second: {
                if(compareSubsetString(pair.second, overlappingSubstring))
                    candidates.push_back(potentialCandidate);
            }
                break;
            case SearchSide::both: {
                if ( compareSubsetString(pair.first, pair.second))
                    candidates.push_back(potentialCandidate);
            }
                break;
        }
    }

    return candidates;
}

std::vector<int> getCandidates(std::vector<int>& state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;

    if (state.empty()) {
        for (size_t i = 0; i < listOfPairs.size(); ++i) {
            auto& pair = listOfPairs[i];
            if (compareSubsetString(pair.first, pair.second)) {
                candidates.push_back(i);
            }
        }
        return candidates;
    }

    std::vector<int> potentialCandidates;

    for (size_t i = 0; i < listOfPairs.size(); ++i) {
        auto it = std::find(state.begin(), state.end(), i);
        if (it == state.end()) {
            potentialCandidates.push_back(i);
        }
    }

    candidates = prune(potentialCandidates, state, listOfPairs);

    return candidates;
}

void serialSearch(std::vector<int> state, std::vector<std::vector<int>>& solutions, const ListOfPairs& listOfPairs)
{
    if (isValidState(state, listOfPairs))
    {
        solutions.emplace_back(state);
    }

    auto candidates = getCandidates(state, listOfPairs);
    for (int candidate : candidates) {
        state.push_back(candidate);
        serialSearch(state, solutions, listOfPairs);
        state.pop_back();
    }
}

std::mutex mtx;

void search(std::vector<int> state, std::vector<std::vector<int>>& solutions, const ListOfPairs& listOfPairs, std::mutex& solutions_mutex)
{
    if (isValidState(state, listOfPairs))
    {
        mtx.lock();
        solutions.emplace_back(state);
        mtx.unlock();
    }
    std::vector<std::future<void>> futures;

    auto candidates = getCandidates(state, listOfPairs);
    for (int candidate : candidates) {
        state.push_back(candidate);
        futures.emplace_back(std::async(std::launch::async, search, state, std::ref(solutions), std::cref(listOfPairs), std::ref(solutions_mutex)));
        state.pop_back();
    }

    for (auto& future : futures) {
        future.wait();
    }
}

std::string solve(const ListOfPairs& listOfPairs) {

    std::vector<int> state;
    std::vector<std::vector<int>> solutions{};
    solutions.reserve(1000);
    for (auto&solution : solutions) {
        solution.reserve(1000);
    }

    std::mutex solutions_mutex;
    search(state, solutions, listOfPairs,solutions_mutex);
    if (solutions.empty()) {
        return "IMPOSSIBLE";
    }

    std::vector<std::string> concatenatedSolutions;
    for (auto const& solution : solutions) {
        std::string concatenatedSolution;
        for (int index : solution) {
            concatenatedSolution += listOfPairs[index].first;
        }
        concatenatedSolutions.emplace_back(concatenatedSolution);
    }
    if (solutions.size() == 1) {
        return concatenatedSolutions[0];
    }

    std::sort(concatenatedSolutions.begin(), concatenatedSolutions.end(), [](auto a, auto b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        return a < b;
    });

    return concatenatedSolutions[0];
}

std::vector<std::string> solveEmilPuzzle(const std::vector<std::vector<std::pair<std::string, std::string>>>& processedInput) {
    std::vector<std::string> solutions;

    for (const auto& pairGroup : processedInput) {
        auto solution = solve(pairGroup);
        solutions.emplace_back(solution);
    }

    return solutions;
}

#ifndef UNIT_TESTING
int main(int argc, char** argv) {
    std::vector<std::vector<std::pair<std::string, std::string>>> listOfGroupsOfPairs;
    std::string inputString;

    std::string line;
    auto it = listOfGroupsOfPairs.begin();
    int numberOfPairs = 0;
    while (std::cin) {
        std::getline(std::cin, line);
        if (numberOfPairs == 0 && !line.empty()) {
            try {
                numberOfPairs = std::stoi(line);
            }
            catch (std::invalid_argument const& ex) {
                break;
            }
            listOfGroupsOfPairs.emplace_back();
            it = listOfGroupsOfPairs.end() - 1;
        }
        else if (!line.empty()) {
            auto pair = splitString(line, ' ');
            it->emplace_back(pair);
            numberOfPairs--;
        }
    }

    auto solutions = solveEmilPuzzle(listOfGroupsOfPairs);

    int caseNumber = 1;
    for (const auto& solution : solutions) {
        std::cout << "Case " << caseNumber++ << ": " << solution << "\n";
    }

    return 0;
}
#endif