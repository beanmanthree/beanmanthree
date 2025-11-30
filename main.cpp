#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <bits/stdc++.h>

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1279, 720), "beanmanthree");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    CircleShape shape(100.f);
    uint32_t x = 540;
    shape.setFillColor(Color::Green);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }
        window.clear();
	shape.setPosition((float)x, 260.f);
        window.draw(shape);
	x++;
	x %= 1280;
        window.display();
    }
    return 0;
}
