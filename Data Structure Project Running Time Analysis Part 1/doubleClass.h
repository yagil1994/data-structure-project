/*////////////////////////////////////////
doubleClass - holds the array's data.
*/////////////////////////////////////////
#pragma once
#include <iostream>
using namespace std;
#include "tools.h"

class doubleClass
{
private:
	int _arrPhySize;
	double* _arr;
	char* scanNumberAndReturnIfValid(bool& Sign)const;//In case the input is not valid, returns nullptr

public:
	doubleClass(int n);
	~doubleClass();

	const double& operator[](int ind)const { return _arr[ind]; }
	double& operator[](int ind) { return _arr[ind]; }

	void insertNumbersToArr();
	int getPhySize()const { return _arrPhySize; }
	double* getDoubleArr() { return _arr; }
	void refreshArr(const double* DoubleArrToCopyFrom);//Returns the array to original order.
};
