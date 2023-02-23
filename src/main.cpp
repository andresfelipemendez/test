#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <numeric>

using ListOfPairs = std::vector<std::pair<std::string,std::string>>;

std::vector<std::string> splitInput(const std::string& input) {
    std::vector<std::string> inputs;
    char const* digits = "0123456789";
    std::size_t n = input.find_first_of(digits);
    while (n != std::string::npos)
    {
        std::size_t const m = input.find_first_not_of(digits, n);
        n = input.find_first_of(digits,m);
        auto res = input.substr(m, n != std::string::npos ? n-m : m);
        inputs.push_back(res);
    }
    return inputs;
}

std::vector<std::string> splitString(const std::string& input, char delimiter){
    std::string string;
    std::istringstream ss(input);
    std::vector<std::string> strings;
    while (std::getline(ss,string, delimiter)) {
        strings.push_back(string);
    }
    return strings;
}

std::vector<std::pair<std::string,std::string>> listOfPairs(const std::string& input) {
    std::vector<std::pair<std::string,std::string>> pairs;
    auto lines = splitString(input,'\n');
    auto it = ++begin (lines); // start from second line
    for (; it != end (lines); ++it) {
        auto word = splitString(*it,' ');
        auto pair = std::make_pair(word[0],word[1]);
        pairs.push_back(pair);
    }
    return pairs;
}

bool isValidState(const std::vector<int>& state, const ListOfPairs& listOfPairs) {
    std::string concatenatedLeft, concatenatedRight;
    for(const int index : state){
        concatenatedLeft += listOfPairs[index].first;
        concatenatedRight += listOfPairs[index].second;
    }
    bool areEqual = concatenatedLeft == concatenatedRight;
    bool areNotEmpty = !concatenatedLeft.empty() || !concatenatedRight.empty();
    return areEqual && areNotEmpty;
}

std::vector<int> getCandidates(std::vector<int> state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;
    std::vector<int> a(listOfPairs.size());
    std::iota(a.begin(), a.end(), 0);
    if(state.empty()) {
        return a;
    }

    for(int i : a) {
        auto it = std::find(state.begin(),state.end(),i);
        if(it == state.end()){
            candidates.push_back(i);
        }
    }

    return candidates;
}

void search(std::vector<int>& state, std::vector<std::vector<int>> &solutions, const ListOfPairs& listOfPairs) {
    if(isValidState(state, listOfPairs))
        solutions.push_back(state);

    auto candidates = getCandidates(state, listOfPairs);
    for(auto& candidate : candidates){
        state.push_back(candidate);
        search(state, solutions, listOfPairs);
        state.pop_back();
    }
}

std::string solve(const ListOfPairs& listOfPairs) {
    std::vector<std::vector<int>> solutions {};
    std::vector<int> state {};
    search(state, solutions,listOfPairs);
    if (solutions.empty()){
        // impossible
        return "IMPOSSIBLE";
    }

    // need to sort and select in alphabetical order
    std::vector<std::string> concatenatedSolutions;
    for(auto const& solution : solutions){
        std::string concatenatedSolution;
        for(int index : solution) {
            concatenatedSolution += listOfPairs[index].first;
        }
        concatenatedSolutions.push_back(concatenatedSolution);
    }
    if(solutions.size() == 1) {
        return concatenatedSolutions[0];
    }

    std::sort(concatenatedSolutions.begin(), concatenatedSolutions.end(), [](auto a, auto b) {
        return a.size() < b.size();
    });
    std::stable_sort(concatenatedSolutions.begin(), concatenatedSolutions.end());
    return concatenatedSolutions[0];
}

std::vector<std::string> solveEmilPuzzle(std::string rawInput) {
    auto splittedInput = splitInput(std::move(rawInput));
    std::vector<std::string> solutions;
    for(const auto& input : splittedInput){
        auto pairs = listOfPairs(input);
        auto solution = solve(pairs);
        solutions.push_back(solution);
    }

    return solutions;
}

int main(int argc, char** argv) {
    std::string inputString;
    while(std::cin) {
        std::string line;
        std::getline(std::cin, line);
        inputString += line + "\n";
    }
    auto solutions = solveEmilPuzzle(inputString);

    int caseNumber = 1;
    for(const auto& solution : solutions) {
        std::cout << "Case " << caseNumber++ << ": " << solution << "\n";
    }

    return 0;
}