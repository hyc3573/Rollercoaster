#include "../include/path.hpp"

Path::Path(const Path& path) : f(StrFunction(path.f.getString())) {};

Path& Path::operator=(const Path& path)
{
	this->f = path.f;
	return *this;
}

void Path::setFunction(string s)
{
	this->f.setString(s);
}

double Path::getHeight(double x)
{
	return f(x);
}

double Path::getSlope(double x)
{
	return (f(x+EPSILON)-f(x))/EPSILON;
}
