/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, mathematical calculation
last changed: 23.07.2020
*/

#include "Calculation.h"

using namespace std;

//constructor for operations with two variables
Calculation::Calculation(double x, double y) : a(x), b(y)
{
	
}
//constructor for operations with one variable
Calculation::Calculation(double x) : a(x) {
	b = 0;
}
Calculation::~Calculation() 
{

}

//adds two numbers
double Calculation::add() 
{
	return a + b;
}

//subtracts two numbers
double Calculation::subtract() {
	return  a - b;
}

//multiplies two numbers
double Calculation::multiply() 
{
	return a * b;
}

//divides two numbers
double Calculation::divide() 
{
	if (b == 0) {
		throw invalidMathOperation("Divide by Zero Error");
	}
	return a / b;
}

//power of number a with number b
double Calculation::power()
{
	return pow(a, b);
}

//root of a number
double Calculation::root()
{
	if (a < 0) {
		throw invalidMathOperation("Root of a negative number Error");
	}
	return sqrt(a);
}