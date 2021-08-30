#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
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

#include "exprtk.hpp"

#include "path.hpp"
#include "constants.hpp"
#include "cart.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;
using namespace sf;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
	RenderWindow window(VideoMode(SCREENWIDTH, SCREENHEIGHT), "Rollercoaster");

	Color backGroundColor = Color::White;
	Color colorOne = Color(0x21, 0x96, 0xf3);
	Color colorOneLight = Color(0x6e, 0xc6, 0xff);
	Color colorOneDark = Color(0x00, 0x69, 0xc0);
	Color colorTwo = Color(0xe9, 0x1e, 0x63);
	Color colorTwoLight = Color(0xff, 0x60, 0x90);
	Color colorTwoDark = Color(0xb0, 0x00, 0x3a);
	Color textColor = Color::Black;

	tgui::GuiSFML gui;
	gui.setTarget(window);

	Path path(
			"1/12800000x^4-1/8000x^3+103/1600x^2-23/2x+800"
	);

	double trackOffset = -600;
	double trackScale = 1;
	double cartOffset = 0;
	double plotInterval = 0.01f;

	Cart cartObj(1, 100, 0, path);

	double dt = 0;

	Clock dtClock;

	CircleShape dot(4);
	dot.setFillColor(colorTwo);
	dot.setOrigin(Vector2f(dot.getLocalBounds().width/2, dot.getLocalBounds().height/2));

	CircleShape cart(5);
	cart.setFillColor(colorOne);
	cart.setOrigin(Vector2f(cart.getLocalBounds().width/2, cart.getLocalBounds().height/2));

	RectangleShape barChartOutline(Vector2f(300, 25));
	barChartOutline.setPosition(400, 50);
	barChartOutline.setOutlineColor(textColor);
	barChartOutline.setOutlineThickness(3);
	barChartOutline.setFillColor(Color::Transparent);

	RectangleShape barChartKE(Vector2f(300, 25));
	barChartKE.setPosition(400, 50);
	barChartKE.setFillColor(colorOne);

	RectangleShape barChartPE(Vector2f(300, 25));
	barChartPE.setOrigin(barChartPE.getLocalBounds().width, barChartPE.getLocalBounds().height);
	barChartPE.setPosition(1000, 75);
	barChartPE.setFillColor(colorTwo);

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

	tgui::EditBox::Ptr exprEnter = tgui::EditBox::create();
	exprEnter->setPosition(50, 110);
	exprEnter->setWidth(tgui::Layout(200));
	exprEnter->setText(path.getFunction());
	exprEnter->onTextChange([&path, &exprEnter]() {
		path.setFunction(exprEnter->getText().toStdString());
	});

	gui.add(exprEnter);

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
						case Keyboard::W:
							trackScale += 0.01;
							break;
						case Keyboard::S:
							trackScale -= 0.01;
							break;
						case Keyboard::A:
							trackOffset += 1;
							break;
						case Keyboard::D:
							trackOffset -= 1;
							break;
						case Keyboard::R:
							cartObj.reset();
							break;
						default: break;
					}
					break;

				default: break;
			}
		}

		dt = dtClock.restart().asSeconds();
		cartObj.update(dt);
		//cout << cartObj.getPE() << " " << cartObj.getKE() << " " << cartObj.getTE() << endl;
		barChartPE.setSize(Vector2f(-cartObj.getPE()/(cartObj.getPE()+cartObj.getKE())*300, barChartPE.getLocalBounds().height));
		barChartKE.setSize(Vector2f(cartObj.getKE()/(cartObj.getPE()+cartObj.getKE())*300, barChartKE.getLocalBounds().height));

		//cout << cartObj.getG() << endl;

		window.clear(backGroundColor);

		for (double i=0;i<SCREENWIDTH;i+=plotInterval)
		{
			dot.setPosition(Vector2f(i, -trackScale*path.getHeight(i)-trackOffset));
			window.draw(dot);
		}

		cart.setPosition(cartObj.getX(), -trackScale*path.getHeight(cartObj.getX())-trackOffset-cartOffset);
		window.draw(cart);

		window.draw(barChartOutline);
		window.draw(barChartKE);
		window.draw(barChartPE);

		gui.draw();

		window.display();
	}

	return 0;
}
