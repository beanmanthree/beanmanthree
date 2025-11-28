#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "beanmanthree");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}