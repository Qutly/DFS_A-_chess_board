#ifndef PAMSI_5_4_DFS_H
#define PAMSI_5_4_DFS_H
#include "Stack.h"
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>

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


void DFS(int board[5][5], Stack<std::pair<int, int>>& stack, std::set<std::pair<int, int>>& visited, std::pair<int, int> start, std::pair<int, int> end) {
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    stack.push(start);
    visited.insert(start);
    visited.insert(start);
    parent[start] = start;

    while (!stack.isEmpty()) {
        std::pair<int, int> current = stack.pop();
        std::cout << "Popping: [" << current.first << "," << current.second << "]\n";
        if (current == end) {
            std::vector<std::pair<int, int>> path;
            std::pair<int, int> node = end;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);

            std::cout << "Path found: ";
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                std::cout << "[" << it->first << "," << it->second << "] ";
            }
            std::cout << "\n";
            return;
        }

        std::vector<std::pair<int, int>> nextSteps = findNext(board, current);
        std::cout << "Next steps: ";
        for (const auto& element: nextSteps) {
            std::cout << "[" << element.first << "," << element.second << "] ";
        }
        for (const auto& next : nextSteps) {
            std::cout << "\nEvaluating: [" << next.first << "," << next.second << "]";
            if (visited.find(next) == visited.end()) {
                stack.push(next);
                visited.insert(next);
                parent[next] = current;
            } else {
                std::cout << "\n[" << next.first << "," << next.second<< "]" << ",already visited, skip";
                continue;
            }
        }
        std::cout << "\nVisited nodes: ";
        for (const auto& visitedNode : visited) {
            std::cout << "[" << visitedNode.first << "," << visitedNode.second << "] ";
        }
        std::cout << "\n";
        stack.print();
    }

    std::cout << "Path not found\n";
}

#endif
