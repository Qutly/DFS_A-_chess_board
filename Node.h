#ifndef PAMSI_5_4_NODE_H
#define PAMSI_5_4_NODE_H

#include <utility>

struct Node {
    std::pair<int, int> coordinates;
    int cost;
    int heuristic;
    Node* parent;

    Node(std::pair<int, int> coords, int g, int h, Node* par = nullptr)
            : coordinates(std::move(coords)), cost(g), heuristic(h), parent(par) {}

    int getTotalCost() const {
        return cost + heuristic;
    }
};

#endif
