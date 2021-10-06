/*
Authors: Robin Schmidt, Jonas Schreiner
Purpose: Calculator GUI Application, storage class of the calculator
last changed: 23.07.2020
*/
#include "Storage.h"

using namespace std;


Storage::Storage()
{

}

Storage::~Storage()
{

}

/*saves a term and the result in a vector
calc is the term and r the result */
void Storage::save(std::string cal, double r)
{
	string result = std::to_string(r);
	result = cutdecimals(result);
	this->result = result;
	latest = cal + "=" + result;
	stored.push_back(latest); 
}
std::string Storage::getCalc(int x) {
	std::string s = stored[x];
	int i = 0;
	std::string n = "";
	while (s[i] != '=') {
		n = n + s[i];
		i++;
	}
	return n;

}

//returns the last result added to the history for the ans button
std::string Storage::getlastresult()
{
	return result;
}

//returns the last evaluated calculation
std::string Storage::getlastcalculation() {
	std::string s = stored.back();
	return s;
}

//cuts unnecessary zeros from saved double values
std::string Storage::cutdecimals(std::string s)
{
	s.erase(s.find_last_not_of('0') + 1, std::string::npos);
	s.erase(s.find_last_not_of('.') + 1, std::string::npos);
	return s;
}

