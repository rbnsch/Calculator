/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, exception for invalid math operations
last changed: 23.07.2020
*/
#include "invalidMathOperation.h"

invalidMathOperation::invalidMathOperation(std::string s)
{
	this->problem = s;	//string with the problem name
}
invalidMathOperation::~invalidMathOperation() {

}
