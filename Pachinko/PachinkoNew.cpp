#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window{ VideoMode{800, 600}, "PAAAAAAAA-CHIN-KO" };
	window.setFramerateLimit(60);

	Event event;

	while (true) {
		window.clear(Color::Black);
		window.pollEvent(event);
		window.display();
	}

	return 0;
}