#include "DFS.h"
#include "Stack.h"


int main() {
    Stack<std::pair<int,int>> stack;
    std::set<std::pair<int, int>> set;
    Stack<std::pair<int,int>> stack2;
    std::set<std::pair<int, int>> set2;

    int board [5][5]
    = {{1,1,1,1,1},
       {1,0,3,0,0},
       {1,0,0,0,0},
       {1,0,0,0,0},
       {1,0,0,0,0}};

    std::pair<int, int> start = std::make_pair(4,2);
    std::pair<int, int> end = std::make_pair(4,1);
    DFS(board, stack, set, start, end);
    return 0;
}
