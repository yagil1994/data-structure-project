#include "doubleClass.h"

doubleClass::doubleClass(int n) :_arrPhySize(n), _arr(new double[_arrPhySize]) {}

doubleClass::~doubleClass()
{
	delete[]_arr;
}

void doubleClass::insertNumbersToArr()
{
	/*
	* getting input into the array: if they're valid it converts them from string to double and put them inside
	*
	*/
	char* currNum = nullptr;
	for (int k = 0; k < _arrPhySize; k++)
	{
		bool numberSign = true;//true is positive, else negative
		currNum = scanNumberAndReturnIfValid(numberSign);//checks the input validation returns nullptr if not valid
		if (currNum)//in case currNum is a valid number
		{
			double theNum = atof(currNum);
			if (!numberSign)
				theNum *= -1;
			_arr[k] = theNum;
			delete[] currNum;// we need to handle it in this case
		}
		else
		{
			cout << "wrong input" << endl;
			exit(1);
		}
		numberSign = true;
	}
}
char* doubleClass::scanNumberAndReturnIfValid(bool& Sign)const
{
	bool isValid = false;
	int strPhySize = 2, totalDigitsCounter = 0, digitsCounterAfterThePoint = 0;
	char* str = new char[strPhySize], ch;
	assert(str);
	bool areThereEnoughDigitsAfterPoint = true;
	ch = getchar();
	while(ch==' '||ch=='\t')//skip the white spaces
		ch = getchar();
	if (ch == '-')//negative number
	{
		Sign = false;
		ch = getchar();
	}
	while (ch != '\0' && !isValid && ch != '\n')
	{
		if (totalDigitsCounter == strPhySize)
			stringRealoc(&str, totalDigitsCounter, strPhySize, strPhySize * 2);

		if (!isDigit(ch) && ch != '.')//if the character is not a digit 
			break;

		str[totalDigitsCounter++] = ch;
		if (ch == '.')//in case we reached the point
		{
			isValid = true;
			break;
		}
		ch = getchar();
	}

	if (isValid)//loop after the decimal point
	{
		stringRealoc(&str, totalDigitsCounter, strPhySize, totalDigitsCounter + 4);
		ch = getchar();
		while (ch != '\0' && isValid && ch != ' ' && ch != '\n')
		{
			if (isDigit(ch))
			{
				digitsCounterAfterThePoint++;
				if (digitsCounterAfterThePoint > 4)
					isValid = false;
				else
				{
					str[totalDigitsCounter++] = ch;
					ch = getchar();
				}
			}
			else if (ch != '\0')
				isValid = false;
		}
	}
	if (!isValid || digitsCounterAfterThePoint < 1)//bad input
	{
		delete[] str;
		return nullptr;
	}
	else
	{
		stringRealoc(&str, totalDigitsCounter, strPhySize, totalDigitsCounter + 1);//minimize to the minimum size
		return str;
	}
}

void doubleClass::refreshArr(const double* DoubleArrToCopyFrom)
{//two of the arrays have the same size in our algorithm
	for (int i = 0; i < _arrPhySize; i++)
		_arr[i] = DoubleArrToCopyFrom[i];
}
