#pragma once
#include <iostream>
using namespace std;
#include <iomanip>
#include "doubleClass.h"
#include <chrono>
#include <fstream>
enum class algorithm { insertion = 0, selection = 1, fives = 2 };

class algorithmClass
{
	private:
		algorithmClass();//we dont want that the user will be able to create an instance of this class
public:
	static double Selection(int left, int right, int i, double* _arr);
	static void insertionSort(doubleClass& arrClass);
	static double fivesAlgorithem(double* arr, int n, int i);
	static int MyPartition(int left, int right, int _pivot, double* _arr);
	static void sortAntPrintI(int i, doubleClass& arrClass);
	static void doubleBubbleSort(int size, double* _arr);
	static void doubleSwap(double& a, double& b);
	static int findIndByNumInDoubleArr(double num, double* arr, int n);
	~algorithmClass() {};
};
