#pragma once
#include <exception>
#include <iostream>

class invalidMathOperation :
	public std::exception
{

public:
	invalidMathOperation(std::string s);
	~invalidMathOperation();
	std::string problem;

};

