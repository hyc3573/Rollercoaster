#include "../include/path.hpp"

Path::Path(const Path& path)
{
	this->f = path.f;
}

Path& Path::operator=(const Path& path)
{
	this->f = path.f;
	return *this;
}

void Path::setFunction(function<real(real)> f)
{
	this->f = f;
}

real Path::getHeight(real x) const
{
	return f(x);
}

real Path::getSlope(real x) const
{
	return (f(x+EPSILON)-f(x))/EPSILON;
}
