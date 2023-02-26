#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <numeric>

using ListOfPairs = std::vector<std::pair<std::string,std::string>>;

std::vector<std::string> splitString(const std::string& input, char delimiter){
    std::string string;
    std::istringstream ss(input);
    std::vector<std::string> strings;
    while (std::getline(ss,string, delimiter)) {
        strings.push_back(string);
    }
    return strings;
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

std::vector<int> prune(const std::vector<int>& potentialCandidates, const std::vector<int>& state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;
    std::string first, second;
    for(int pairIndex : state){
        first += listOfPairs[pairIndex].first;
        second += listOfPairs[pairIndex].second;
    }
    // I need the "overlapping" substring to match in the next pair on the oppoite side
    std::string overlappingSubstring;
    int side = 0;
    if(first.size() < second.size()) {
        overlappingSubstring = second.substr(first.size(), second.size() - first.size());
        side = 1;
    } else if (first.size() > second.size()) {
        overlappingSubstring = first.substr(second.size(), first.size() - second.size());
        side = 2;
    } else if (first.size() == second.size()){
        overlappingSubstring = first;
        side = 3;
    }

    for(int potentialCandidate : potentialCandidates) {
        auto pair = listOfPairs[potentialCandidate];
        if(side == 1) {
            std::string overlappingOppositeSubstring = pair.first.substr(0, overlappingSubstring.size());
            if(overlappingSubstring == overlappingOppositeSubstring)
                candidates.push_back(potentialCandidate);
        } else if (side == 2) {
            std::string overlappingOppositeSubstring = pair.second.substr(0, overlappingSubstring.size());
            if(overlappingSubstring == overlappingOppositeSubstring)
                candidates.push_back(potentialCandidate);
        } else if (side == 3 ) {
            // check what string can fit the substring?
            std::string overlappingOppositeSubstring = pair.second.substr(0, overlappingSubstring.size());
            if(overlappingSubstring == overlappingOppositeSubstring)
                candidates.push_back(potentialCandidate);
        }
    }


    return candidates;
}

bool compareSubsetString(const std::string& first, const std::string& seccond) {
    if(first.size() == seccond.size())
        return first == seccond;
    const auto& shortestString = first.size() > seccond.size() ? seccond : first;
    const auto& longestString = first.size() < seccond.size() ? seccond : first;
    const auto subString = longestString.substr(0,shortestString.size());
    return subString == shortestString;
}

std::vector<int> getCandidates(std::vector<int> state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;

    if(state.empty()) {
        for (int i = 0; i < listOfPairs.size(); ++i) {
            const auto& pair = listOfPairs[i];

            if(compareSubsetString(pair.first, pair.second)) {
                candidates.push_back(i);
            }
        }
        return candidates;
    }

    std::vector<int> potentialCandidates, a(listOfPairs.size());
    std::iota(a.begin(), a.end(), 0);
    for(int i : a) {
        auto it = std::find(state.begin(),state.end(),i);
        if(it == state.end()){
            potentialCandidates.push_back(i);
        }
    }

    candidates = prune(potentialCandidates, state, listOfPairs);


    return candidates;
}

void search(std::vector<int>& state, std::vector<std::vector<int>> &solutions, const ListOfPairs& listOfPairs) {
    if(isValidState(state, listOfPairs)){
        solutions.push_back(state);
        return;
    }

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

std::vector<std::vector<std::pair<std::string,std::string>>> processInput(const std::string& input) {
    // number of input groups
    std::vector<std::vector<std::pair<std::string,std::string>>> listOfGroupsOfPairs;
    auto splitted = splitString(input, '\n');

    int numberOfPairs = 0;
    auto it = listOfGroupsOfPairs.begin();
    for(std::string line : splitted) {
        if(numberOfPairs == 0) {
            numberOfPairs = std::stoi(line);
            listOfGroupsOfPairs.push_back({});
            it = listOfGroupsOfPairs.end() - 1;
        } else {
            auto pair = splitString(line, ' ');
            it->push_back({pair[0], pair[1]});
            numberOfPairs--;
        }
    }

    return listOfGroupsOfPairs;
}

std::vector<std::string> solveEmilPuzzle(const std::string& rawInput) {
    auto processedInput = processInput(rawInput);
    std::vector<std::string> solutions;

    for(const auto& pairGroup : processedInput){
        auto solution = solve(pairGroup);
        solutions.push_back(solution);
    }

    return solutions;
}

//int main(int argc, char** argv) {
//    std::string inputString;
//    while(std::cin) {
//        std::string line;
//        std::getline(std::cin, line);
//        inputString += line + "\n";
//    }
//
//    auto solutions = solveEmilPuzzle(inputString);
//
//    int caseNumber = 1;
//    for(const auto& solution : solutions) {
//        //    std::cout << solution << "\n";
//        std::cout << "Case " << caseNumber++ << ": " << solution << "\n";
//    }
//
//    return 0;
//}