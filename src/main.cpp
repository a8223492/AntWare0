#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
    RenderWindow window(
            VideoMode(800, 600),
            "My first Window",
            Style::Resize
    );
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}