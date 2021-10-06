#pragma once
#include "Calculation.h"
#include "Storage.h"
#include <iostream>
#include <vector>

class Evaluate
{
public:
	Evaluate(std::string s);
	~Evaluate();
	double analyse();

private:

	double calculate(std::vector <std::string> input);
	double oneOperator(std::string s, std:: string t);
	double twoOperator(std::string s, std::string t, std::string calc);
	std::vector<std::string> rank0op(std::vector<std::string> inputstr);
	std::vector<std::string> rank1op(std::vector<std::string> inputstr);
	std::vector<std::string> rank2op(std::vector<std::string> inputstr);
	std::vector<std::string> rank3op(std::vector<std::string> inputstr);
	std::vector<std::string> rank4op(std::vector<std::string> inputstr);
	std::string input;
	int rank3;
	int rank4;
	int rank2;
	int rank1;
	int rank0;
};
