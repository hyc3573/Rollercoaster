#ifndef PATH_HPP
#define PATH_HPP

#include <functional>
#include "constants.hpp"

using namespace std;

/*class Path
{
	public:
		Path() {};

		virtual void setAmp(real newAmp) = 0;
		virtual void setXOffset(real newOffset) = 0;
		virtual void setYOffset(real newOffset) = 0;

		virtual real getHeight(real x) = 0;
		virtual real getSlope(real x) = 0;
};*/

class Path
{
	public:
		Path(function<real(real)> f) : f(f) {};
		Path(const Path& path);
		Path& operator=(const Path& path);

		void setFunction(function<real(real)> f);
		real getHeight(real x) const;
		real getSlope(real x) const;

	private:
		function<real(real)> f;
};

#endif
