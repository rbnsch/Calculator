#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>


class Storage
{
public:
	Storage();
	~Storage();
	void save(std::string cal, double result);
	std::string getlastresult();
	std::string getCalc(int i);
	std::string getlastcalculation();

private:
	std::string result;
	std::string cutdecimals(std::string s);
	std::string latest;
	std::vector <std::string> stored;
};

