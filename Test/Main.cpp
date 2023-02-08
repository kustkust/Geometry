#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include <iomanip>

template<class T>
struct Item {
	T item;
	Item() = default;
};

void testRectRect() {
	if (false) {
		auto r1 = gm::makeShape<gm::Rectangle>(gm::Coord{ 0,0 }, gm::Size{ 10,10 });
		auto r2 = gm::makeShape<gm::Rectangle>(gm::Coord{ 1,1 }, gm::Size{ 5,5 });
		auto col = r1.collides(r2);
		std::cout << "";
	}
	if (true) {
		auto r1 = gm::makeShape<gm::Rectangle>(gm::Coord{ 0,0 }, gm::Size{ 10,10 });
		auto r2 = gm::makeShape<gm::Rectangle>(gm::Coord{ 5,5 }, gm::Size{ 10,10 });
		auto col = r1.collides(r2);
		std::cout << "";
	}
}

void testCircRect() {
	if (true) {
		auto rsh = gm::makeShape<gm::Rectangle>(gm::Coord{ 0,0 }, gm::Size{ 10,10 });
		auto csh = gm::makeShape<gm::Circle>(gm::Coord{ 0,0 }, 5);
		auto col = rsh.collides(csh);
		std::cout << "";
	}
	if (true) {
		auto rsh = gm::makeShape<gm::Rectangle>(gm::Coord{ 0,0 }, gm::Size{ 10,10 });
		auto csh = gm::makeShape<gm::Circle>(gm::Coord{ 5,5 }, 5);
		auto col = rsh.collides(csh);
		std::cout << "";
	}
	if (true) {
		auto rsh = gm::makeShape<gm::Rectangle>(gm::Coord{ 0,0 }, gm::Size{ 10,10 });
		auto csh = gm::makeShape<gm::Circle>(gm::Coord{ 5,5 }, sqrt(25 + 25));
		auto col = rsh.collides(csh);
		std::cout << "";
	}
	if (true) {
		auto rsh = gm::makeShape<gm::Rectangle>(gm::Coord{ 1,-1 }, gm::Size{ 2,2 });
		auto csh = gm::makeShape<gm::Circle>(gm::Coord{ 0,0 }, 2);
		auto col = rsh.collides(csh);
		std::cout << "";
	}
	return;
}

void f(const gm::Vector& v, const gm::Vector& u) {
	std::cout << v << "^" << u << "=" << std::setprecision(2) << (v ^ u)*gm::RtoG << std::endl;
}

void testAngle() {
	f({ -2, 1 }, { -2, -1 });
	f({ -2, -1 }, { -2, 1 });
	f({ 1, 1 }, { -2, -1 });
	f({ -1, 1 }, { -2, -1 });
	f({ 2, 1 }, { -1, -2 });
	f({ 1, 1 }, { 1, -1 });
	system("pause");
}

int main() {
	testAngle();
	testCircRect();
	testRectRect();
	sf::RenderWindow window(sf::VideoMode(640, 480), "Awesome Game");

	sf::Texture texture;

	//texture.setRepeated(true);

	if (!texture.loadFromFile("res/img/Player.png")) {
		std::cout << "Load failed" << std::endl;

		system("pause");
	}

	sf::Sprite sprite(texture);

	// sprite.setTextureRect(sf::IntRect(0, 0, 600, 600));

	//sprite.setColor(sf::Color(255, 255, 255, 64));

	while (window.isOpen()) {
		sf::Event event;

		// handle all events
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();

				break;
			}
		}

		// update the game

		window.clear();

		window.draw(sprite);

		window.display();
	}

	return EXIT_SUCCESS;
}