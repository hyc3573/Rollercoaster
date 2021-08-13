#include <SFML/System/Clock.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <TGUI/Backends/SFML/GuiSFML.hpp>
#include <TGUI/Layout.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBox.hpp>
#include <iostream>
#include <cmath>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>

#include <TGUI/TGUI.hpp>
#include <string>

#include "../include/exprtk.hpp"

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

	tgui::GuiSFML gui;
	gui.setTarget(window);

	Path path(
			"1.0/12800000.0*x^4-1.0/8000.0*x^3+103.0/1600.0*x^2-23.0/2.0*x+600.0"
	);

	double trackOffset = -600;
	double trackScale = 1;
	double cartOffset = 0;
	double plotInterval = 0.1f;

	Cart cartObj(1, 100, 0, path);

	double dt = 0;

	Clock dtClock;

	CircleShape dot(2);
	dot.setFillColor(Color::Red);
	dot.setOrigin(Vector2f(dot.getLocalBounds().width/2, dot.getLocalBounds().height/2));

	CircleShape cart(5);
	cart.setFillColor(Color::Blue);
	cart.setOrigin(Vector2f(cart.getLocalBounds().width/2, cart.getLocalBounds().height/2));

	tgui::Button::Ptr gUpButton = tgui::Button::create();
	gUpButton->setPosition(50, 50);
	gUpButton->setWidth(tgui::Layout(30));
	gUpButton->setText(U"+");
	gUpButton->onClick([&cartObj]() {cartObj.setG(cartObj.getG()+5);});

	tgui::Button::Ptr gDownButton = tgui::Button::create();
	gDownButton->setPosition(180, 50);
	gDownButton->setWidth(tgui::Layout(30));
	gDownButton->setText(U"-");
	gDownButton->onClick([&cartObj]() {cartObj.setG(cartObj.getG()-5);});

	tgui::EditBox::Ptr gEnter = tgui::EditBox::create();
	gEnter->setPosition(80, 50);
	gEnter->setWidth(tgui::Layout(100));
	gEnter->setInputValidator(U"[0-9.]*");
	gEnter->setText(to_string(cartObj.getG()));
	gEnter->onTextChange([&cartObj, &gEnter]() {
		cartObj.setG(gEnter->getText().toFloat());
	});

	gUpButton->onClick([&gEnter]() {
		gEnter->setText(to_string(gEnter->getText().toFloat()+5));
	});
	gDownButton->onClick([&gEnter]() {
		gEnter->setText(to_string(gEnter->getText().toFloat()-5));
	});

	gui.add(gUpButton);
	gui.add(gDownButton);
	gui.add(gEnter);

	tgui::Button::Ptr mUpButton = tgui::Button::create();
	mUpButton->setPosition(50, 80);
	mUpButton->setWidth(tgui::Layout(30));
	mUpButton->setText(U"+");
	mUpButton->onClick([&cartObj]() {cartObj.setMass(cartObj.getMass()+5);});

	tgui::Button::Ptr mDownButton = tgui::Button::create();
	mDownButton->setPosition(180, 80);
	mDownButton->setWidth(tgui::Layout(30));
	mDownButton->setText(U"-");
	mDownButton->onClick([&cartObj]() {cartObj.setMass(cartObj.getMass()-5);});

	tgui::EditBox::Ptr mEnter = tgui::EditBox::create();
	mEnter->setPosition(80, 80);
	mEnter->setWidth(tgui::Layout(100));
	mEnter->setInputValidator(U"[0-9.]*");
	mEnter->setText(to_string(cartObj.getMass()));
	mEnter->onTextChange([&cartObj, &mEnter]() {
		cartObj.setMass(mEnter->getText().toFloat());
	});

	mUpButton->onClick([&mEnter]() {
		mEnter->setText(to_string(mEnter->getText().toFloat()+5));
	});
	mDownButton->onClick([&mEnter]() {
		mEnter->setText(to_string(mEnter->getText().toFloat()-5));
	});

	gui.add(mUpButton);
	gui.add(mDownButton);
	gui.add(mEnter);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			gui.handleEvent(event);
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;

				case Event::KeyPressed:
					switch (event.key.code)
					{
						case Keyboard::Up:
							trackScale += 0.01;
							break;
						case Keyboard::Down:
							trackScale -= 0.01;
							break;
						case Keyboard::Left:
							trackOffset += 1;
							break;
						case Keyboard::Right:
							trackOffset -= 1;
							break;
						case Keyboard::Q:
							cartObj.setG(cartObj.getG()+10);
							break;
						case Keyboard::W:
							cartObj.setG(cartObj.getG()-10);
							break;
						case Keyboard::E:
							cartObj.setMass(cartObj.getMass()+10);
							break;
						case Keyboard::R:
							cartObj.setMass(cartObj.getMass()-10);
							break;
						default: break;
					}
					break;

				default: break;
			}
		}

		dt = dtClock.restart().asSeconds();
		cartObj.update(dt);

		//cout << cartObj.getG() << endl;

		window.clear(Color::Black);

		for (double i=0;i<SCREENWIDTH;i+=plotInterval)
		{
			dot.setPosition(Vector2f(i, -trackScale*path.getHeight(i)-trackOffset));
			window.draw(dot);
		}

		cart.setPosition(cartObj.getX(), -trackScale*path.getHeight(cartObj.getX())-trackOffset-cartOffset);
		window.draw(cart);

		gui.draw();

		window.display();
	}

	return 0;
}
