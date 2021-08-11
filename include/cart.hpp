#ifndef CART_HPP
#define CART_HPP

#include "constants.hpp"
#include "path.hpp"

class Cart
{
	public:
		Cart(real mass, real g, real x0, const Path& path) : mass(mass), g(g), x0(x0), path(path), x(0), lastX(0), KE(0), TE(0), PE(0), v(0), dir(0) {reset();};

		void setMass(real mass);
		void setG(real g);
		void setPath(const Path& path);

		void reset();
		void update(real dt);

		real getX() const;
		real getMass() const;
		real getG() const;
		real getTE() const;
		real getV() const;

		Path getPath() const;

	private:
		real mass;
		real g;
		real x0;
		real x;
		real lastX;
		real v;
		real dir;

		real KE;
		real TE;
		real PE;

		Path path;
};

real calcPE(const Cart& cart);
real calcPE(real height, real mass, real g);
real calcKE(real TE, real PE);
real calcKE(const Cart& cart);

#endif
