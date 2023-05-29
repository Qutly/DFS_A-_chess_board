#ifndef PAMSI_5_4_DFS_H
#define PAMSI_5_4_DFS_H
#include "Stack.h"
#include <iostream>
#include <vector>
#include <utility>
#include <set>


std::vector<std::pair<int,int>> findNext(int board[5][5], std::pair<int,int> coordinates) {
    std::vector<std::pair<int, int>> nextCoords;

    if(coordinates.first - 2 > 0 && coordinates.second + 1 > 0 && coordinates.first - 2 <=4 && coordinates.second + 1 <=4)
        nextCoords.emplace_back(coordinates.first - 2, coordinates.second + 1); //checked (1prawo 2góra)

    if(coordinates.first - 1 > 0 && coordinates.second + 2 > 0 && coordinates.first - 1 <=4 && coordinates.second + 2 <=4)
        nextCoords.emplace_back(coordinates.first - 1, coordinates.second + 2); //checked (2prawo 1góra)

    if(coordinates.first + 1 > 0 && coordinates.second + 2 > 0 && coordinates.first + 1 <=4 && coordinates.second + 2 <=4)
        nextCoords.emplace_back(coordinates.first + 1, coordinates.second + 2); //checked (2prawo 1dół)

    if(coordinates.first + 2 > 0 && coordinates.second + 1 > 0 && coordinates.first + 2 <=4 && coordinates.second + 1 <=4)
        nextCoords.emplace_back(coordinates.first + 2, coordinates.second + 1); //checked (1prawo 2dół)

    if(coordinates.first + 2 > 0 && coordinates.second - 1 > 0 && coordinates.first + 2 <=4 && coordinates.second - 1 <=4)
        nextCoords.emplace_back(coordinates.first + 2, coordinates.second - 1); //checked (1lewo 2dół)

    if(coordinates.first + 1 > 0 && coordinates.second - 2 > 0 && coordinates.first + 1 <=4 && coordinates.second - 2 <=4)
        nextCoords.emplace_back(coordinates.first + 1, coordinates.second - 2); //checked (2lewo 1dół)

    if(coordinates.first - 1 > 0 && coordinates.second - 2 > 0 && coordinates.first - 1 <=4 && coordinates.second - 2 <=4)
        nextCoords.emplace_back(coordinates.first - 1, coordinates.second - 2); //checked (2lewo 1góra)

    if(coordinates.first - 2 > 0 && coordinates.second - 1 > 0 && coordinates.first - 2 <=4 && coordinates.second - 1 <=4)
        nextCoords.emplace_back(coordinates.first - 2, coordinates.second - 1); //checked (1lewo 2góra)

    return nextCoords;
}

void DFS(int board[5][5], Stack<std::pair<int, int>>& stack, std::set<std::pair<int, int>> set,std::pair<int, int> start, std::pair<int, int> end) {
    int i;
    std::vector<std::pair<int,int>> nextSteps;
    std::vector<std::pair<int,int>> path;
    stack.push(start);
    set.insert(start);
    while (!stack.isEmpty()) {
        std::cout << "\n";
        std::pair<int, int> n = stack.pop();
        path.push_back(n);
        std::cout << "Popping" << " [" << n.first << "," << n.second << "]" << "\n";
        std::cout << "Is" << " [" << n.first << "," << n.second << "]" << " my goal?" << "\n";
        if(n == end) {
            std::cout << "[" << n.first << "," << n.second << "] " << "element found" << "\n";
            std::cout << "Path: ";
            for(const auto& element : path ) {
                std::cout << "[" << element.first << "," << element.second << "] ";
            }
            return;
        }
        std::cout << "No" << "\n";
        nextSteps = findNext(board, n);
        std::cout << "Next steps: ";
        for(const auto& element: nextSteps) {
            std::cout << "[" << element.first << "," << element.second << "] ";
        }
        std::cout << "\n";
        for(i = 0; i < nextSteps.size(); i++) {
            std::cout << "Evaluating: " << "[" << nextSteps[i].first << "," << nextSteps[i].second << "]" << "\n";
            auto it = set.find(nextSteps[i]);
            if(it != set.end()) {
                std::cout << "["<<it->first << "," << it->second << "]" << " already visited, skip" << "\n";
                continue;
            }
            set.insert(nextSteps[i]);
            stack.push(nextSteps[i]);
            std::cout << "Visited nodes: ";
            for(const auto& element: set) {
                std::cout << "[" << element.first << "," << element.second << "] ";
            }
            std::cout << "\n";
            stack.print();
        }
    }
}




#endif
