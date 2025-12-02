#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

std::unordered_set<std::uint64_t> cells;

inline std::uint64_t encode(int x, int y) {
    return (std::uint64_t(std::uint32_t(x)) << 32) | std::uint32_t(y);
}

void next() {
    static const int DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
}

int main() {
    cells.reserve(65536);
    sf::RenderWindow window(sf::VideoMode(1279, 720), "beanmanthree");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    sf::CircleShape shape(100.f);
    std::uint32_t x = 540;
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
