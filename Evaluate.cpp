/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, evaluation of term
last changed: 23.07.2020
*/

#include "Evaluate.h"
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

Evaluate::Evaluate(string s)
{
	this->input = s;	//input string
	//rank of different operations, the lower the number the higher the importance
	rank1 = 0;			//number of operations with rank 1(root) in a term
	rank2 = 0;			//number of operations with rank 2(power) in a term
	rank3 = 0;			//number of operations with rank 3(multiply or divide) in a term
	rank4 = 0;			//number of operations with rank 4(add or subtract) in a term
}

Evaluate::~Evaluate()
{
}

/*Evaluates terms with one Operator
string s is the number and string t the operator
returns a double */
double Evaluate::oneOperator(string s, string t) {
	double x = stod(s);
	double r;
	Calculation calculation(x);
	if (t == "r") {
		r = calculation.root();
	}
	return r;
}

/*Evaluates terms with two Operators
string s is the first number, string t the second number and calc the operator
returns a double */
double Evaluate::twoOperator(string s, string t, string calc)
{
	double r;
	double x = stod(s);
	double y = stod(t);

	Calculation calculation(x, y);
	if (calc == "+") {
		r = calculation.add();
	}
	else if (calc == "-") {
		r = calculation.subtract();
	}
	else if (calc == "*") {
		r = calculation.multiply();
	}
	else if (calc == "/") {
		r = calculation.divide();
	}
	else if (calc == "^") {
		r = calculation.power();
	}
	return r;
}



/*analyses the input string the object was initialized with and splits numbers and operators into a vector in order
then evaluates the term and returns the result */
double Evaluate::analyse()
{
	int i = 0;
	int j = 0;
	int size = input.length();

	vector<string> inputstr(50);



	while (input[i] != NULL) {
		if (!((input[i] <= 57 && input[i] >= 48) || input[i] == 46)) {
			if (input[i] == '-' && (i == 0 || !((input[i - 1] <= 57 && input[i - 1] >= 48) || input[i - 1] == 46))) {
				inputstr[j] = inputstr[j] + input[i];
			}
			else {
				j++;

				if (input[i] == '(') {
					rank0++;
					j--;
				}
				
				if (input[i] == 'r') {
					rank1++;
					j--;
				}
				if (input[i] == '^') {
					rank2++;
				}
				if (input[i] == '*' || input[i] == '/') {
					rank3++;
				}
				else if (input[i] == '+' || input[i] == '-') {
					rank4++;
				}

				inputstr[j] = input[i];

				if (input[i] == ')') {
					j--;
				}

				j++;

				
			}

		}
		else {

			inputstr[j] = inputstr[j] + input[i];
		}

		i++;
	}
	return(calculate(inputstr));
}

//computes the term and executes operations in correct order
double Evaluate::calculate(std::vector<std::string> input) {
	std::vector<std::string> inputstr = input;
	std::vector<std::string> s(50);
	
	/*
	if (rank0 > 0) {
		inputstr = rank0op(inputstr) {

		}
	}
	*/

	if (rank1 > 0) {
		inputstr = rank1op(inputstr);
	}
	if (rank2 > 0) {
		inputstr = rank2op(inputstr);
	}
	if (rank3 > 0) {
		inputstr = rank3op(inputstr);
	}
	if (rank4 > 0) {
		inputstr = rank4op(inputstr);
	}
	return stod(inputstr[0]);
}

/*
std::vector<std::string> Evaluate::rank0op(std::vector<std::string> inputstr) {

}
*/

//calculates all rank 1 operations (root) until none are left
std::vector<std::string> Evaluate::rank1op(std::vector<std::string> inputstr) {
	std::vector<std::string> op(50);
	int i = 0;
	int j = 0;
	while (rank1 > 0) {
		if (inputstr[i] == "r") {
			double x = oneOperator(inputstr[i + 1], inputstr[i]);
			op[j] = to_string(x);
			i++;
			rank1--;
		}
		else {
			op[j] = inputstr[i];
		}
		j++;
		i++;
	}

	while (inputstr[i] != "") {
		op[j] = inputstr[i];
		j++;
		i++;
	}

	return op;
}

//calculates all rank 2 operations (power) until none are left
std::vector<std::string> Evaluate::rank2op(std::vector<std::string> inputstr) {
	std::vector<std::string> op(50);


	int i = 0;
	int j = 0;
	while (rank2 > 0) {
		if (inputstr[i] == "^") {

			double ab = twoOperator(op[j - 1], inputstr[i + 1], inputstr[i]);
			op[j - 1] = to_string(ab);
			i++;
			rank2--;
			j = j - 1;
		}
		else {
			op[j] = inputstr[i];
		}
		j++;
		i++;
	}

	while (inputstr[i] != "") {
		op[j] = inputstr[i];
		j++;
		i++;
	}

	return op;
}

//calculates all rank 3 operations (multiply / divide) until none are left
std::vector<std::string> Evaluate::rank3op(std::vector<std::string> inputstr) {
	std::vector<std::string> op(50);


	int i = 0;
	int j = 0;
	while (rank3> 0) {
		if ((inputstr[i] == "*" || inputstr[i] == "/")) {

			double ab = twoOperator(op[j - 1], inputstr[i + 1], inputstr[i]);
			op[j - 1] = to_string(ab);
			i++;
			rank3--;
			j = j - 1;
			//oper = true;
		}
		else {
			op[j] = inputstr[i];
		}
		j++;
		i++;
	}

	while (inputstr[i] != "") {
		op[j] = inputstr[i];
		j++;
		i++;
	}

	return op;

}

//calculates all rank 4 operations (add / subtract) until none are left
std::vector<std::string> Evaluate::rank4op(std::vector<std::string> inputstr) {
	std::vector<std::string> op(50);


	int i = 0;
	int j = 0;
	while (rank4 > 0) {
		if ((inputstr[i] == "+" || inputstr[i] == "-")) {
			
			double ab = twoOperator(op[j-1], inputstr[i + 1], inputstr[i]);
			op[j-1] = to_string(ab);
			i++;
			rank4--;
			j = j - 1;
		}
		else {
			op[j] = inputstr[i];
		}
		j++;
		i++;
	}

	while (inputstr[i] != "") {
		op[j] = inputstr[i];
		j++;
		i++;
	}

	return op;
}

