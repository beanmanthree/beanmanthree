#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

std::unordered_set<uint64_t> cells;

inline uint64_t encode(int32_t x, int32_t y) {
    return (uint64_t(uint32_t(x)) << 32) | uint32_t(y);
}

inline void decode(uint64_t cell, int32_t& x, int32_t& y) {
    x = static_cast<int32_t>(cell >> 32);
    y = static_cast<int32_t>(cell & 0xFFFFFFFF);
    return;
}

inline uint64_t shiftCell(uint64_t cell, int x, int y) {
    return encode(static_cast<int32_t>((cell >> 32) + x), static_cast<int32_t>((cell & 0xFFFFFFFF) + y));
}

inline void addCell(int32_t x, int32_t y) {
    cells.insert(encode(x, y));
}

void next() {
    static const int8_t DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int8_t DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::unordered_map<uint64_t, uint8_t> update;
    for (const uint64_t& cell : cells) {
        update[cell] += 16;
        for (int i = 0; i < 8; i++) update[shiftCell(cell, DX[i], DY[i])]++;
    }
    for (const auto& [pos, neighbors] : update) {
        if (neighbors & 16) {
            if (neighbors != 18 && neighbors != 19) cells.erase(pos);
        } else if (neighbors == 3) cells.insert(pos);
    }
    return;
}

inline void drawCells(sf::RenderWindow& window, sf::Color& cellColor, uint32_t cellSize, int32_t xOffset, int32_t yOffset) {
    sf::Vector2u windowSize = window.getSize();
    int32_t minX = (xOffset / cellSize) - 1;
    int32_t maxX = ((xOffset + windowSize.x) / cellSize) + 1;
    int32_t minY = (yOffset / cellSize) - 1;
    int32_t maxY = ((yOffset + windowSize.y) / cellSize) + 1;
    sf::VertexArray quads(sf::Quads);
    int32_t x, y;
    for (uint64_t cell : cells) {
        decode(cell, x, y);
        if (x < minX || x > maxX || y < minY || y > maxY) continue;
        float screenX = static_cast<float>(x * cellSize - xOffset);
        float screenY = static_cast<float>(y * cellSize - yOffset);
        quads.append(sf::Vertex(sf::Vector2f(screenX, screenY), cellColor));
        quads.append(sf::Vertex(sf::Vector2f(screenX + cellSize, screenY), cellColor));
        quads.append(sf::Vertex(sf::Vector2f(screenX + cellSize, screenY + cellSize), cellColor));
        quads.append(sf::Vertex(sf::Vector2f(screenX, screenY + cellSize), cellColor));
    }
    window.draw(quads);
    return;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "beanmanthree");
    window.setFramerateLimit(60);
    cells.reserve(65536);
    sf::Color cellColor = sf::Color::White;
    uint32_t cellSize = 10;
    int32_t xOffset = 0, yOffset = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                uint64_t clickedCell = encode((event.mouseButton.x + xOffset) / cellSize, (event.mouseButton.y + yOffset) / cellSize);
                if (cells.contains(clickedCell)) cells.erase(clickedCell);
                else cells.insert(clickedCell);
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F) next();
            }
        }
        window.clear();
        drawCells(window, cellColor, cellSize, xOffset, yOffset);
        window.display();
    }
    return 0;
}
