#include "tools.h"

double* cloneDoubleArray(double* arrayToClone, int size)
{
    double* newDoubleArr = new double[size];
    for (int i = 0; i < size; i++)
        newDoubleArr[i] = arrayToClone[i];
    return newDoubleArr;
}

bool isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}
bool isNumAnExponenetOf5(int num)
{
    // Repeatedly comput power of 5 
    int pow = 1;
    while (pow < num)
        pow *= 5;
    // Check if power of 5 becomes num 
    return (pow == num);
}
void stringRealoc(char** src, int logS,int& phyS, int newTotalSizeToAlocate)
{
    int i;
    char* tmp = new char[newTotalSizeToAlocate];
    for (i = 0; i < logS; i++)
        tmp[i] = (*src)[i];
    tmp[i] = '\0';
    delete[](*src);
    *src = tmp;
    phyS = newTotalSizeToAlocate;
}



