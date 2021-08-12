#include "../include/cart.hpp"

#include <cmath>
#include <iostream>

using namespace std;

real calcPE(real height, real mass, real g)
{
	return height*mass*g;
}

real calcPE(const Cart& cart)
{
	return calcPE(cart.getPath().getHeight(cart.getX()), cart.getMass(), cart.getG());
}

real calcKE(real TE, real PE)
{
	return TE - PE;
}

real calcKE(const Cart& cart)
{
	return calcKE(cart.getTE(), calcPE(cart));
}

void Cart::setG(real g)
{
	if (g > 0)
	{
		this->g = g;
		calcTE();
	}
}

void Cart::setMass(real mass)
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

real Cart::getX() const
{
	return x;
}

real Cart::getMass() const
{
	return mass;
}

real Cart::getG() const
{
	return g;
}

real Cart::getTE() const
{
	return TE;
}

real Cart::getV() const
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

void Cart::update(real dt)
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
	real slope = path.getSlope(x);
	lastX = x;
	x += v*dt*dir/sqrt(1+slope*slope);
}
