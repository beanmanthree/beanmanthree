#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

std::unordered_set<uint64_t> cells;

inline uint64_t encode(int x, int y) {
    return (uint64_t(uint32_t(x)) << 32) | uint32_t(y);
}

inline uint64_t shiftCell(uint64_t pos, int x, int y) {
    return encode(static_cast<int32_t>((pos >> 32) + x), static_cast<int32_t>((pos & 0xFFFFFFFF) + y));
}

inline void addCell(int x, int y) {
    cells.insert(encode(x, y));
}

void next() {
    static const int DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::unordered_map<uint64_t, uint8_t> update;
    for (const uint64_t& cell : cells) {
        update[cell] += 16;
        for (int i = 0; i < 8; i++) update[shiftCell(cell, DX[i], DY[i])]++;
    }
    cells.clear();
    for (const auto& [pos, neighbors] : update) {
        if (neighbors & 16) {
            if (neighbors == 18 || neighbors == 19) cells.insert(pos);
        }
        else if (neighbors == 3) cells.insert(pos);
    }
    return;
}

int main() {
    cells.reserve(65536);
    sf::RenderWindow window(sf::VideoMode(1279, 720), "beanmanthree");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    uint32_t x = 540;
    shape.setFillColor(sf::Color::Green);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear();
        shape.setPosition((float)x, 260.f);
        window.draw(shape);
        x += 7;
        x %= 1280;
        window.display();
    }
    return 0;
}
