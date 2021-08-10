#include "../include/path.hpp"

void Path::setFunction(function<real(real)> f)
{
	this->f = f;
}

real Path::getHeight(real x)
{
	return f(x);
}

real Path::getSlope(real x)
{
	return (f(x+EPSILON)-f(x))/EPSILON;
}
