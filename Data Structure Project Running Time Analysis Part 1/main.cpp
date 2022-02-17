//Yagil Sofer ID: 205433808 & Amir Mizrachi ID:311128763
#include "algorithmClass.h"

int main()
{
	int n, i;
	cin >> n >> i;
	if (n <= 0 || i > n || i < 1)
	{
		cout << "wrong input " << endl;
		exit(1);
	}
	doubleClass arrayToSort(n);
	cin.ignore();
	arrayToSort.insertNumbersToArr();
	algorithmClass::sortAntPrintI(i, arrayToSort);
	return 0;

}
