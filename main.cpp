#include <string>
#include <exception>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <functional>
#include "state.h"
#include "rungekutta.h"

template <typename T>
double deg2rad(T theta)
{
	return theta * 3.15159265358979 / 180.0;
}

template <typename T>
double rad2deg(T rad)
{
	return rad * 180.0 / 3.14159265358979;
}

int main(void)
{
	sf::RenderWindow window(sf::VideoMode(1200, 675), "SFML window");

	window.setVerticalSyncEnabled(true);

	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;

	const double diff = 1.0 / 60.0;
	movement<System, movedata> mov(deg2rad(60.0), deg2rad(95.0), 200, diff/2);

	while (window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		sf::Event event;
		

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}

		sf::CircleShape shape(30.f);
		shape.setFillColor(sf::Color::White);
		sf::CircleShape shape2(30.f);
		shape2.setFillColor(sf::Color::White);

		shape.setPosition(300.0 * std::sin(mov.getcurrentstep().theta) - 30.0 + 600.0, 300 * std::cos(mov.getcurrentstep().theta) - 30.0);
		shape2.setPosition(300.0 * std::sin(mov.getcurrentstep().theta) + 600.0 + 300.0 * std::sin(mov.getcurrentstep().pi) - 60.0, 300.0 * std::cos(mov.getcurrentstep().theta) + 300.0 * std::cos(mov.getcurrentstep().pi) - 60.0);

		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(600.0f, 0.0f)),
			sf::Vertex(sf::Vector2f(300.0 * std::sin(mov.getcurrentstep().theta) + 600.0, 300.0 * std::cos(mov.getcurrentstep().theta)))
		};

		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(300.0 * std::sin(mov.getcurrentstep().theta) + 600.0, 300 * std::cos(mov.getcurrentstep().theta))),
			sf::Vertex(sf::Vector2f(300.0 * std::sin(mov.getcurrentstep().theta) + 600.0 + 300 * std::sin(mov.getcurrentstep().pi) - 30.0, 300.0 * std::cos(mov.getcurrentstep().theta) + 300.0 * std::cos(mov.getcurrentstep().pi) - 30.0))
		};

		mov.deletesteps(1);
		if (mov.stepnum() < 200)
		{
			mov.calcsteps(5, diff/2);
		}

		window.clear();
		
		window.draw(shape);
		window.draw(line, 2, sf::Lines);

		window.draw(shape2);
		window.draw(line2, 2, sf::Lines);

		window.display();
		
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
		previousTime = currentTime;
	}
	return 0;
}