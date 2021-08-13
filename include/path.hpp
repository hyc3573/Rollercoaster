#ifndef PATH_HPP
#define PATH_HPP

#include <cmath>
#include <functional>
#include <string>
#include <iostream>
#include <vector>
#include "constants.hpp"
#include "exprtk.hpp"

using namespace std;

/*class Path
{
	public:
		Path() {};

		virtual void setAmp(double newAmp) = 0;
		virtual void setXOffset(double newOffset) = 0;
		virtual void setYOffset(double newOffset) = 0;

		virtual double getHeight(double x) = 0;
		virtual double getSlope(double x) = 0;
};*/

class StrFunction
{
	public:
		StrFunction(string s) : s(s), x(0)
		{
			symbols.add_variable("x", x);
			expression.register_symbol_table(symbols);

			if (!parser.compile(s, expression))
			{
				cout << "Compile Error!" << endl;
			}
		}

		StrFunction(const StrFunction& f)
		{
			this->s = f.getString();
		}

		void setString(string s)
		{
			this->s = s;
			if (!parser.compile(s, expression))
			{
				cout << "Compile Error!" << endl;
			}
		}

		string getString() const 
		{
			return s;
		}

		double operator()(double x)
		{
			this->x = x;
			return expression.value();
		}
		
		StrFunction& operator=(const StrFunction& path)
		{
			this->s = path.getString();
			return *this;
		}

	private:
		string s;
		double x;
		
		exprtk::symbol_table<double> symbols;
		exprtk::expression<double> expression;
		exprtk::parser<double> parser;
};

class Path
{
	public:
		Path(string s) : f(s) {};

		Path(const Path& path);
		Path& operator=(const Path& path);

		void setFunction(string s);
		double getHeight(double x);
		double getSlope(double x);

	private:
		StrFunction f;
};

#endif
