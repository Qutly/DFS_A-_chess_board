#ifndef PAMSI_5_4_A_H
#define PAMSI_5_4_A_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
#include <algorithm>
#include "Node.h"

int heuristic(const std::pair<int, int>& start, const std::pair<int, int>& goal) {
    return std::abs(start.first - goal.first) + std::abs(start.second - goal.second);
}

bool isValid(const std::pair<int, int>& coordinates) {
    int x = coordinates.first;
    int y = coordinates.second;
    return x > 0 && x < 15 && y > 0 && y < 15;
}

void aStarSearch(std::pair<int, int> start, std::pair<int, int> goal, sf::RenderWindow &window, sf::RectangleShape squares[15][15]) {

    sf::Texture textureKnight;
    sf::Texture textureKing;
    sf::Texture textureRook;

    if(textureKnight.loadFromFile("../assets/knight.png")) {
        squares[start.first][start.second].setTexture(&textureKnight);
        window.draw(squares[start.first][start.second]);
    }

    if(textureRook.loadFromFile("../assets/rook.png")) {
        squares[0][0].setTexture(&textureRook);
        window.draw(squares[0][0]);
    }

    std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> pq([](Node* a, Node* b) {
        return a->getTotalCost() > b->getTotalCost();
    });

    std::vector<std::pair<int, int>> nextCoords;
    std::vector<std::vector<bool>> visited(15, std::vector<bool>(15, false));

    Node* rootNode = new Node(start, 0, heuristic(start, goal));
    pq.push(rootNode);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        std::pair<int, int> currentCoords = current->coordinates;
        visited[currentCoords.first][currentCoords.second] = true;

        std::cout << "Visited Node: (" << currentCoords.first << ", " << currentCoords.second << "), Cost: " << current->cost << std::endl;
        squares[currentCoords.first][currentCoords.second].setFillColor(sf::Color::Yellow);
        window.draw(squares[currentCoords.first][currentCoords.second]);
        window.display();

        if (currentCoords == goal) {
            std::vector<std::pair<int, int>> path;
            while (current != nullptr) {
                path.push_back(current->coordinates);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            std::cout << "Path found: ";
            for (const auto& coords : path) {
                std::cout << "(" << coords.first << ", " << coords.second << ") ";
                squares[coords.first][coords.second].setTexture(&textureKnight);
                squares[coords.first][coords.second].setFillColor(sf::Color::Green);
                window.draw(squares[coords.first][coords.second]);
                window.display();
                squares[coords.first][coords.second].setTexture(nullptr);
                window.draw(squares[coords.first][coords.second]);
            }
            return;
        }

        nextCoords = findNext(currentCoords);

        for (const auto& coords : nextCoords) {
            if (!visited[coords.first][coords.second] && isValid(coords)) {
                int newCost = current->cost + 1;
                Node* newNode = new Node(coords, newCost, heuristic(coords, goal), current);
                pq.push(newNode);

                std::cout << "Chosen Node: (" << coords.first << ", " << coords.second << "), Cost: " << newCost << std::endl;
                squares[coords.first][coords.second].setFillColor(sf::Color::Blue);
                window.draw(squares[coords.first][coords.second]);
                window.display();
            }
        }
    }
}




#endif
