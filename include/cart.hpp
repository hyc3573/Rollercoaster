#ifndef CART_HPP
#define CART_HPP

#include "constants.hpp"
#include "path.hpp"

class Cart
{
	public:
		Cart(double mass, double g, double x0, const Path& path) : mass(mass), g(g), x0(x0), path(path), x(0), lastX(0), KE(0), TE(0), PE(0), v(0), dir(0) {reset();};

		void setMass(double mass);
		void setG(double g);
		void setPath(const Path& path);

		void calcTE();
		void reset();
		void update(double dt);

		double getX() const;
		double getMass() const;
		double getG() const;
		double getTE() const;
		double getV() const;
		double getKE() const;
		double getPE() const;

		Path getPath() const;

	private:
		double mass;
		double g;
		double x0;
		double x;
		double lastX;
		double v;
		double dir;

		double KE;
		double TE;
		double PE;

		Path path;
};

double calcPE(const Cart& cart);
double calcPE(double height, double mass, double g);
double calcKE(double TE, double PE);
double calcKE(const Cart& cart);

#endif
