#include "DFS.h"
#include "Stack.h"
#include "A*.h"
#include <SFML/Graphics.hpp>

int main() {
    int option;
    const int width = 15;
    const int height = 15;
    int board [height][width];
//    = {{1,1,1,1,1},
//       {1,0,0,0,0},
//       {1,0,0,0,0},
//       {1,0,0,0,0},
//       {1,0,0,0,0}};
    for (int i = 0; i < height; i++) {
        board[i][0] = 1;
    }
    for (int j = 0; j < width; j++) {
        board[0][j] = 1;
    }

    for (int i = 1; i < height; i++) {
        for (int j = 1; j < width; j++) {
            board[i][j] = 0;
        }
    }
    std::cout << "Choose algorithm: " << "1.DFS" << " 2.A*" << "\n";
    std::cin >> option;
    std::cout << "\n";

    Stack<std::pair<int,int>> stack;
    std::set<std::pair<int, int>> set;

    std::pair<int, int> start = std::make_pair(1,1);
    std::pair<int, int> end = std::make_pair(13,10);

    sf::RenderWindow window(sf::VideoMode(650, 650), "Path Finding", sf::Style::Titlebar | sf::Style::Close & ~sf::Style::Resize);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    float centerX = static_cast<float>(desktop.width - window.getSize().x) / 2.0f;
    float centerY = static_cast<float>(desktop.height - window.getSize().y) / 2.0f;

    window.setPosition(sf::Vector2i(static_cast<int>(centerX), static_cast<int>(centerY)));

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    sf::RectangleShape squares[height][width];

    const float squareSize = 30.f;
    const float squareSpacing = 3.f;
    float totalWidth = (width * squareSize) + ((width - 1) * squareSpacing);
    float totalHeight = (height * squareSize) + ((height - 1) * squareSpacing);
    float startX = (window.getSize().x - totalWidth) / 2.f;
    float startY = (window.getSize().y - totalHeight) / 2.f;

    bool performFunction = true;
    window.clear();
    while (window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                float posX = startX + (x * (squareSize + squareSpacing));
                float posY = startY + (y * (squareSize + squareSpacing));
                squares[y][x].setSize(sf::Vector2f(squareSize, squareSize));
                squares[y][x].setPosition(posX, posY);
                squares[y][x].setFillColor(sf::Color(200, 200, 200));
                window.draw(squares[y][x]);
            }
        }
        if(performFunction) {
            if(option == 1) {
                DFS(stack, set, start, end, window, squares);
            }
            if(option == 2) {
                aStarSearch(start, end, window, squares);
            }
            performFunction = false;
        }
    }
    return 0;
}

