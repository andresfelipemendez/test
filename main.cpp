#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <set>

struct State{
    std::vector<int> current;
};

using ListOfPairs = std::vector<std::pair<std::string,std::string>>;

std::pair<std::string,std::string> splitString(const std::string& input, char delimiter){
    auto pos = input.find(delimiter);
    auto fisrt = input.substr(0, pos);
    auto second = input.substr( pos + 1, input.size() - 1);
    return { fisrt, second };
}

bool isValidState(const State& state, const ListOfPairs& listOfPairs) {
    std::string concatenatedLeft, concatenatedRight;
    for(const int index : state.current){
        concatenatedLeft += listOfPairs[index].first;
        concatenatedRight += listOfPairs[index].second;
    }
    bool areEqual = concatenatedLeft == concatenatedRight;
    bool areNotEmpty = !concatenatedLeft.empty() || !concatenatedRight.empty();
    return areEqual && areNotEmpty;
}

std::vector<int> prune(const std::vector<int>& potentialCandidates, State& state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;
    std::string first, second;
    for(int pairIndex : state.current){
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
                candidates.emplace_back(potentialCandidate);
        } else if (side == 2) {
            std::string overlappingOppositeSubstring = pair.second.substr(0, overlappingSubstring.size());
            if(overlappingSubstring == overlappingOppositeSubstring)
                candidates.emplace_back(potentialCandidate);
        } else if (side == 3 ) {
            // check what string can fit the substring?
            std::string overlappingOppositeSubstring = pair.second.substr(0, overlappingSubstring.size());
            if(overlappingSubstring == overlappingOppositeSubstring)
                candidates.emplace_back(potentialCandidate);
        }
    }

    return candidates;
}

bool compareSubsetString(const std::string& first, const std::string& second) {
    if(first.size() == second.size())
        return first == second;
    const auto& shortestString = first.size() > second.size() ? second : first;
    const auto& longestString = first.size() < second.size() ? second : first;
    const auto subString = longestString.substr(0,shortestString.size());
    return subString == shortestString;
}

std::vector<int> getCandidates(State& state, const ListOfPairs& listOfPairs) {
    std::vector<int> candidates;

    if(state.current.empty()) {
        for (int i = 0; i < listOfPairs.size(); ++i) {
            const auto& pair = listOfPairs[i];

            if(compareSubsetString(pair.first, pair.second)) {
                candidates.emplace_back(i);
            }
        }
        return candidates;
    }

    std::vector<int> potentialCandidates;
    for (int i = 0; i < listOfPairs.size(); ++i)
    {
        auto it = std::find(state.current.begin(),state.current.end(),i);
        if(it == state.current.end()){
            potentialCandidates.emplace_back(i);
        }
    }

    candidates = prune(potentialCandidates, state, listOfPairs);

    return candidates;
}

void search(State& state, std::vector<State> &solutions, const ListOfPairs& listOfPairs) {
    
    if(isValidState(state, listOfPairs)){
        solutions.emplace_back(state);
        return;
    }

    auto candidates = getCandidates(state, listOfPairs);
    for(auto& candidate : candidates){
        state.current.insert(candidate);
        search(state, solutions, listOfPairs);
        state.current.erase(candidate);
    }
}

std::string solve(const ListOfPairs& listOfPairs) {
    
    std::vector<State> solutions {};
    State state;

    search(state, solutions,listOfPairs);
    if (solutions.empty()){
        return "IMPOSSIBLE";
    }

    // need to sort and select in alphabetical order
    std::vector<std::string> concatenatedSolutions;
    for(auto const& solution : solutions){
        std::string concatenatedSolution;
        for(int index : solution.current) {
            concatenatedSolution += listOfPairs[index].first;
        }
        concatenatedSolutions.emplace_back(concatenatedSolution);
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



std::vector<std::string> solveEmilPuzzle(const std::vector<std::vector<std::pair<std::string,std::string>>>& processedInput) {
    std::vector<std::string> solutions;

    for(const auto& pairGroup : processedInput){
        auto solution = solve(pairGroup);
        solutions.emplace_back(solution);
    }

    return solutions;
}

int main(int argc, char** argv) {
    
    std::vector<std::vector<std::pair<std::string,std::string>>> listOfGroupsOfPairs;
    std::string inputString;

    std::string line;
    auto it = listOfGroupsOfPairs.begin();
    int numberOfPairs = 0;
    while( std::cin) {
        std::getline(std::cin, line);
        if(numberOfPairs == 0 && !line.empty()) {
            try {
                numberOfPairs = std::stoi(line);
            } catch (std::invalid_argument const& ex) {
                break;
            }
            listOfGroupsOfPairs.emplace_back();
            it = listOfGroupsOfPairs.end() - 1;
        } else if(!line.empty()){
            auto pair = splitString(line, ' ');
            it->emplace_back(pair);
            numberOfPairs--;
        }
    }

    auto solutions = solveEmilPuzzle(listOfGroupsOfPairs);

    int caseNumber = 1;
    for(const auto& solution : solutions) {
        std::cout << "Case " << caseNumber++ << ": " << solution << "\n";
    }
    
    return 0;
}