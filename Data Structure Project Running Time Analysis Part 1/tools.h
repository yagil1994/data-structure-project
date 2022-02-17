/*////////////////////////////////////////
Global functions - used by multiple classes.
*/////////////////////////////////////////
#pragma once
#include <iostream>
using namespace std;
#include<math.h>
#include <assert.h>
double* cloneDoubleArray(double* arrayToClone, int size);
bool isNumAnExponenetOf5(int num);
bool isDigit(char ch);
void stringRealoc(char** src, int logS, int& phyS, int newTotalSizeToAlocate);
