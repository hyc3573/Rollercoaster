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
#include "../include/cart.hpp"

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREENWIDTH, SCREENHEIGHT), "Rollercoaster");

	Path path(
		[](real x)->real 
		{
			return 1.f/12800000.f*pow(x,4)-1.f/8000.f*pow(x,3)+103.f/1600.f*pow(x,2)-23.f/2.f*x+600;
		}
	);

	real trackOffset = -530;
	real cartOffset = 0;
	real plotInterval = 0.1f;

	Cart cartObj(1, 500, 0, path);

	real dt = 0;

	Clock dtClock;

	CircleShape dot(2);
	dot.setFillColor(Color::Red);
	dot.setOrigin(Vector2f(dot.getLocalBounds().width/2, dot.getLocalBounds().height/2));

	CircleShape cart(5);
	cart.setFillColor(Color::Blue);
	cart.setOrigin(Vector2f(cart.getLocalBounds().width/2, cart.getLocalBounds().height/2));

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

		dt = dtClock.restart().asSeconds();
		cartObj.update(dt);

		//cout << path.getHeight(cartObj.getX()) << endl;

		window.clear(Color::Black);

		for (real i=0;i<SCREENWIDTH;i+=plotInterval)
		{
			dot.setPosition(Vector2f(i, -path.getHeight(i)-trackOffset));
			window.draw(dot);
		}

		cart.setPosition(cartObj.getX(), -path.getHeight(cartObj.getX())-trackOffset-cartOffset);
		window.draw(cart);

		window.display();
	}

	return 0;
}
