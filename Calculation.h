#pragma once
#include <iostream>
#include "invalidMathOperation.h"
#include <math.h>

class Calculation
{
public:
	Calculation(double x, double y);
	Calculation(double x);
	~Calculation();
	double add();
	double subtract();
	double multiply();
	double divide();
	double power();
	double root();

protected:
	double a;
	double b;

};

