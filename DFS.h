#ifndef PAMSI_5_4_DFS_H
#define PAMSI_5_4_DFS_H
#include <SFML/Graphics.hpp>
#include "Stack.h"
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>

std::vector<std::pair<int,int>> findNext(std::pair<int,int> coordinates) {
    std::vector<std::pair<int, int>> nextCoords;

    if(coordinates.first - 2 > 0 && coordinates.second + 1 > 0 && coordinates.first - 2 < 15 && coordinates.second + 1 < 15)
        nextCoords.emplace_back(coordinates.first - 2, coordinates.second + 1); //checked (1prawo 2góra)

    if(coordinates.first - 1 > 0 && coordinates.second + 2 > 0 && coordinates.first - 1 < 15 && coordinates.second + 2 < 15)
        nextCoords.emplace_back(coordinates.first - 1, coordinates.second + 2); //checked (2prawo 1góra)

    if(coordinates.first + 1 > 0 && coordinates.second + 2 > 0 && coordinates.first + 1 < 15 && coordinates.second + 2 < 15)
        nextCoords.emplace_back(coordinates.first + 1, coordinates.second + 2); //checked (2prawo 1dół)

    if(coordinates.first + 2 > 0 && coordinates.second + 1 > 0 && coordinates.first + 2 < 15 && coordinates.second + 1 < 15)
        nextCoords.emplace_back(coordinates.first + 2, coordinates.second + 1); //checked (1prawo 2dół)

    if(coordinates.first + 2 > 0 && coordinates.second - 1 > 0 && coordinates.first + 2 < 15 && coordinates.second - 1 < 15)
        nextCoords.emplace_back(coordinates.first + 2, coordinates.second - 1); //checked (1lewo 2dół)

    if(coordinates.first + 1 > 0 && coordinates.second - 2 > 0 && coordinates.first + 1 < 15 && coordinates.second - 2 < 15)
        nextCoords.emplace_back(coordinates.first + 1, coordinates.second - 2); //checked (2lewo 1dół)

    if(coordinates.first - 1 > 0 && coordinates.second - 2 > 0 && coordinates.first - 1 < 15 && coordinates.second - 2 < 15)
        nextCoords.emplace_back(coordinates.first - 1, coordinates.second - 2); //checked (2lewo 1góra)

    if(coordinates.first - 2 > 0 && coordinates.second - 1 > 0 && coordinates.first - 2 < 15 && coordinates.second - 1 < 15)
        nextCoords.emplace_back(coordinates.first - 2, coordinates.second - 1); //checked (1lewo 2góra)

    return nextCoords;
}


void DFS(Stack<std::pair<int, int>>& stack, std::set<std::pair<int, int>>& visited, std::pair<int, int> start, std::pair<int, int> end, sf::RenderWindow &window, sf::RectangleShape squares[15][15]) {
    int iterator = 0;
    sf::Font font;
    sf::Text text;
    sf::Texture textureKnight;
    sf::Texture textureRook;
    sf::Texture textureKing;
    if(textureKnight.loadFromFile("../assets/knight.png")) {
        squares[start.first][start.second].setTexture(&textureKnight);
        window.draw(squares[start.first][start.second]);
    }

    if(textureRook.loadFromFile("../assets/rook.png")) {
        squares[0][0].setTexture(&textureRook);
        window.draw(squares[0][0]);
    }

    if(textureKing.loadFromFile("../assets/king.png")) {
        squares[end.first][end.second].setTexture(&textureKing);
        window.draw(squares[end.first][end.second]);
    }

    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    stack.push(start);
    visited.insert(start);
    parent[start] = start;
    bool isPathFound = false;

    while (!stack.isEmpty()) {
        std::pair<int, int> current = stack.pop();
        std::cout << "Popping: [" << current.first << "," << current.second << "]\n";
        squares[current.first][current.second].setFillColor(sf::Color::Yellow);
        window.draw(squares[current.first][current.second]);
        window.display();

        if (current == end) {
            isPathFound = true;
            break;
        }

        std::vector<std::pair<int, int>> nextSteps = findNext(current);
        std::cout << "Next steps: ";
        for (const auto& element: nextSteps) {
            std::cout << "[" << element.first << "," << element.second << "] ";
            if(squares[element.first][element.second].getFillColor() != sf::Color::Yellow) {
                squares[element.first][element.second].setFillColor(sf::Color::Blue);
                window.draw(squares[element.first][element.second]);
                window.display();
            }
        }

        for (const auto& next : nextSteps) {
            std::cout << "\nEvaluating: [" << next.first << "," << next.second << "]";
            if (visited.find(next) == visited.end()) {
                stack.push(next);
                visited.insert(next);
                parent[next] = current;
            } else {
                std::cout << "\n[" << next.first << "," << next.second<< "]" << ",already visited, skip";
            }
        }

        std::cout << "\nVisited nodes: ";
        for (const auto& visitedNode : visited) {
            std::cout << "[" << visitedNode.first << "," << visitedNode.second << "] ";
        }
        std::cout << "\n";
        stack.print();
    }

    if (isPathFound) {
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
            if(font.loadFromFile("../assets/arial.ttf")) {

                text.setString(std::to_string(iterator));
                text.setFont(font);
                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(15);
                text.setPosition(squares[it->first][it->second].getPosition().x + 8, squares[it->first][it->second].getPosition().y + 6);

                squares[it->first][it->second].setFillColor(sf::Color::Green);
                squares[it->first][it->second].setTexture(&textureKnight);
                window.draw(squares[it->first][it->second]);
                window.display();

                squares[it->first][it->second].setTexture(nullptr);
                window.draw(squares[it->first][it->second]);
                window.draw(text);
                iterator++;
            }
        }
        std::cout << "\n";
    } else {
        std::cout << "Path not found\n";
    }
}


#endif
