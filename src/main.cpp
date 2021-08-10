#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>

#include "../include/path.hpp"
#include "../include/constants.hpp"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREENWIDTH, SCREENHEIGHT), "Rollercoaster");

	Path path(
		[](real x)->real{return 3.f/800.f*(x-400)*(x-400);}
	);

	real x = EPSILON;
	real g = 100;
	real m = 1;

	real trackOffset = -600;
	real cartOffset = 10;
	real plotInterval = 0.1f;

	real TE = m*g*path.getHeight(0);

	real PE = m*g*path.getHeight(x);
	real KE = TE-PE; 

	real dir = 1;

	real dt = 0;

	Clock dtClock;

	CircleShape dot(2);
	dot.setFillColor(Color::Red);
	dot.setOrigin(Vector2f(dot.getLocalBounds().width/2, dot.getLocalBounds().height/2));

	CircleShape cart(5);
	cart.setFillColor(Color::Blue);
	cart.setOrigin(Vector2f(cart.getLocalBounds().width/2, cart.getLocalBounds().height/2));

	real lastX = x;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		PE = m*g*path.getHeight(x);
		KE = TE-PE;

		if (KE < 0)
		{
			//cout << "a" <<endl;
			x = lastX;
			dir *= -1;
			PE = m*g*path.getHeight(x);
			KE = TE-PE;
		}

		real v = sqrt(2*KE);
		real slope = path.getSlope(x);
		dt = dtClock.restart().asSeconds();
		lastX = x;
		x += v*dt*dir/sqrt(1+slope*slope);

		//cout << path.getHeight(x) << endl;

		window.clear(Color::Black);

		for (real i=0;i<SCREENWIDTH;i+=plotInterval)
		{
			dot.setPosition(Vector2f(i, -path.getHeight(i)-trackOffset));
			window.draw(dot);
		}

		cart.setPosition(Vector2f(x, -path.getHeight(x)-trackOffset-cartOffset));
		window.draw(cart);

		window.display();
	}

	return 0;
}
