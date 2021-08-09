#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREENWIDTH, SCREENHEIGHT), "Rollercoaster");

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

	window.clear(Color::Black);



	window.display();
	}

	return 0;
}
