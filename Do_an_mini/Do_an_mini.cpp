#include <iostream>
#include <string>
#include <iomanip>
#include "Bailam.h"
#include <conio.h>
using namespace std;

void Print_Reserve_Polish_Notation(string P)
{
	queue<string> Q;
	string P1 = P;
	infix_to_postfix(P1, Q);
	cout << "Reserve Polish Notation : ";
	while (!Q.empty())
	{
		cout << Q.front() << " ";
		Q.pop();
	}
	cout << endl;
}

int main()
{
	string P;

	cout << "Input Expression : ";
	getline(cin, P);

	Xuli(P);

	if (Checkvalid(P) == false)
	{
		cout << "Expression invalid" << endl;
		return 1;
	}

	double value = Calculate(P);

	cout << "Output : " << setprecision(11) << value << endl;

	getch();

	return 0;
}

