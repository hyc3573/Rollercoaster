#include "../include/cart.hpp"

#include <cmath>
#include <iostream>

using namespace std;

double calcPE(double height, double mass, double g)
{
	return height*mass*g;
}

double calcPE(const Cart& cart)
{
	return calcPE(cart.getPath().getHeight(cart.getX()), cart.getMass(), cart.getG());
}

double calcKE(double TE, double PE)
{
	return TE - PE;
}

double calcKE(const Cart& cart)
{
	return calcKE(cart.getTE(), calcPE(cart));
}

void Cart::setG(double g)
{
	if (g > 0)
	{
		this->g = g;
		calcTE();
	}
}

void Cart::setMass(double mass)
{
	if (mass > 0)
	{
		this->mass = mass;
		calcTE();
	}
}

void Cart::setPath(const Path &path)
{
	this->path = path;
	calcTE();
}

double Cart::getX() const
{
	return x;
}

double Cart::getMass() const
{
	return mass;
}

double Cart::getG() const
{
	return g;
}

double Cart::getTE() const
{
	return TE;
}

double Cart::getV() const
{
	return v;
}

Path Cart::getPath() const
{
	return path;
}

void Cart::calcTE()
{
	TE = path.getHeight(x0)*mass*g;
}

void Cart::reset()
{
	x = x0 + EPSILON;
	lastX = x;
	calcTE();
	dir = 1;
}

void Cart::update(double dt)
{
	if (calcKE(*this) < 0)
	{
		x = lastX;
		dir *= -1;
	}

	PE = calcPE(*this);
	KE = calcKE(TE, PE);
	//cout << KE << endl;

	v = sqrt(2*KE/mass);
	double slope = path.getSlope(x);
	lastX = x;
	x += v*dt*dir/sqrt(1+slope*slope);
}
