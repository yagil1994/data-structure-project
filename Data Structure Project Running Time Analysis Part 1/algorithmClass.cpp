#include "algorithmClass.h"

void algorithmClass::insertionSort( doubleClass& arrClass)
{
	int k, j;
	double* _arr = arrClass.getDoubleArr(), key;
	for (k = 1; k < arrClass.getPhySize(); k++)
	{
		key = _arr[k];
		j = k - 1;
		while (j >= 0 && _arr[j] > key)
		{
			_arr[j + 1] = _arr[j];
			j = j - 1;
		}
		_arr[j + 1] = key;
	}
}

int algorithmClass::MyPartition(int left, int right, int _pivot, double* _arr)
{
	int pivot = left, index = right;
	bool direction = true;//indicates the index location :false=left ,true=right;
	doubleSwap(_arr[_pivot], _arr[left]);

	while (pivot != index)
	{
		if ((_arr[pivot] > _arr[index]) && direction || (_arr[pivot] < _arr[index]) && !direction)
		{
			doubleSwap(_arr[pivot], _arr[index]);
			int tmpInd = pivot;
			pivot = index;
			if (direction)// it means now the index is in the right and we are going to swap it to the left and then move it forward.
			{
				direction = false;
				index = tmpInd + 1;
			}
			else
			{
				direction = true;
				index = tmpInd - 1;
			}
		}
		else if (direction)//if the index is in the right side
			index--;
		else
			index++;
	}
	return pivot + 1;
}

double algorithmClass::Selection(int left, int right, int i, double* _arr)
{
	int pivot, leftOverPart;
	pivot = MyPartition(left, right, left, _arr) - 1;
	leftOverPart = pivot - left + 1;
	if (i == leftOverPart)
		return _arr[pivot];
	if (i < leftOverPart)
		return Selection(left, pivot - 1, i, _arr);
	else
		return Selection(pivot + 1, right, i - leftOverPart, _arr);
}

int algorithmClass::findIndByNumInDoubleArr(double num, double* arr, int n)
{
	//gets a number and returns it's index in the array- we know it exists there. 
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == num)
			return i + 1;//(indexes start in one in the algorithm)
	}
}

double algorithmClass::fivesAlgorithem(double* arr, int n, int i)
{
	if (n <= 5)//halt point
	{
		doubleBubbleSort(n, arr);
		return arr[i - 1];
	}
	int remain = n % 5;
	int BsizeWithRemainder = (n/5);
	if (remain != 0)
		BsizeWithRemainder++;
		 
	double* B = new double[BsizeWithRemainder];//B will have the medians' array inside
	assert(B);
	for (int t = 0; t < n / 5; t++)//sorting the n/5 parts of the main array
	{
		doubleBubbleSort(5, arr + t * 5);
		B[t] = (arr + t * 5)[2];//putting inside B the current median
	}

	if (remain != 0)//in case we have any remain
	{
		doubleBubbleSort(remain, arr + n- remain);
		int medianLocation = ceil(static_cast<double>(remain) / 2);
		B[BsizeWithRemainder - 1] = (arr + n -remain)[medianLocation-1];//putting inside B the current median
	}
	
	int remain2 = BsizeWithRemainder % 5;
	int BsizeWithRemainder2 = (BsizeWithRemainder / 5);
	if (remain2 != 0)
		BsizeWithRemainder2++;
	double median = fivesAlgorithem(B, BsizeWithRemainder2, ceil(static_cast<double>(BsizeWithRemainder2)/2));//getting the half value from the B array
	delete[] B;
	int medianIndex = findIndByNumInDoubleArr(median, arr, n);//getting the median's index in the main array
	int k = MyPartition(0, n - 1, medianIndex, arr);
	if (k > i)
		return fivesAlgorithem(arr, k - 1, i);
	else if (k < i)
		return fivesAlgorithem(arr + k, n - k, i - k);
	else
		return arr[k - 1];
}

void algorithmClass::sortAntPrintI(int i, doubleClass& arrClass)
{
	/*
	* in this function we use all the algorithms that required in the assignment and check the running time,
	* in addtition we print the 'I number in his size" three times after each algorithm 
	*/
	ofstream myfile("Measure.txt"); // The name of the file
	if (!myfile)
	{
		cout << "Error: File did not open." << endl;
		exit(1);
	}
	double* _arr = arrClass.getDoubleArr();
	int _arrPhySize = arrClass.getPhySize();
	double* _backUpArr = cloneDoubleArray(_arr, _arrPhySize);
	for (int k = 0; k < 3; k++)//each iteration findes and print the i according to other algorithm
	{
		auto start = chrono::high_resolution_clock::now();
		// unsync the I/O of C and C++.
		ios_base::sync_with_stdio(false);
		switch (k)
		{
			case static_cast<int>(algorithm::insertion):
			{		//insertion sort
				insertionSort(arrClass);
				cout << fixed << "Insertion sort i'th element: " << setprecision(4) << _arr[i - 1] << endl;
				break;
			}
			case static_cast<int>(algorithm::selection):
			{
				//selection
				Selection(0, _arrPhySize - 1, i, _arr);
				cout << fixed << "Selection i'th element: " << setprecision(4) << _arr[i - 1] << endl;
				break;
			}
			case static_cast<int>(algorithm::fives) :
			{
				//fivesAlgorithem
				fivesAlgorithem(_arr, _arrPhySize, i);
				cout << fixed << "Quintuplet algorithm i'th element: " << setprecision(4) << _arr[i - 1] << endl;
				break;
			}
		}
		auto end = chrono::high_resolution_clock::now();
		// Calculating total time taken by the program.
		double time_taken =
			chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		time_taken *= 1e-9;
		if (k == 0)
		{
			myfile << "Time taken by function <insertionSort> is : " << fixed
				<< time_taken << setprecision(9);
		}
		else if (k == 1)
		{
			myfile << "Time taken by function <Selection> is : " << fixed
				<< time_taken << setprecision(9);
		}
		else if (k == 2)
		{
			myfile << "Time taken by function <fivesAlgorithem> is : " << fixed
				<< time_taken << setprecision(9);
		}
		myfile << " sec" << endl;
		arrClass.refreshArr(_backUpArr);//returns the array to his natural appearance for the next iteration
	}
	delete[] _backUpArr;
	myfile.close();
}
void algorithmClass::doubleBubbleSort(int size, double* _arr)
{
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1; j++)
		{
			if (_arr[j] > _arr[j + 1])
				doubleSwap(_arr[j], _arr[j + 1]);
		}
}
void algorithmClass::doubleSwap(double& a, double& b)
{
	double tmp = a;
	a = b;
	b = tmp;
}