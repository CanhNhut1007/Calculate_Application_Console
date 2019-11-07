#include "Bailam.h"

int Priority(string s)
{
	if (s == "+" || s == "-")
		return 1;
	else if (s == "*" || s == "/")
		return 2;
	else if (s == "^")
		return 3;
	else if (s == "#")
		return 4;
	return 0;
}

int isOperator(string s)
{
	if (Priority(s) == 0)
	{
		if (s == ")" || s == "(")
			return 0;
		return 1;
	}
	return 2;
}

void XuliKhoangTrang(string &P)
{
	for (int i = 0; i < P.length(); i++)
	{
		if (P[i] == ' ')
		{
			P.erase(P.begin() + i);
			i--;
		}
	}
}

int Process(string P,int i)
{
	if (P[i - 1] == '(' && P[i] == '-')
	{
		for (int j = i + 2; j < P.length(); j++)
		{
			if (P[j] == ')')
				return true;
			else if (P[j] < '0' || P[j] > '9')
				return false;
		}
	}
	return false;
}

void Xuli(string &P)
{
	XuliKhoangTrang(P);

	if (P[0] == '-')
	{
		P.insert(0, "(");
		for (int j = 2; j < P.length(); j++)
		{
			if (P[j] < '0' || P[j] > '9')
			{
				P.insert(j, ")");
				break;
			}
		}
	}

	for (int i = 1; i < P.length(); i++)
	{
		string s1(1, P[i - 1]);

		if ((P[i-1] =='(' || P[i - 1] == '*' 
			|| P[i - 1] == '^' || P[i - 1] == '+' 
			|| P[i - 1] == '-' || P[i - 1] == '/') 
			&& P[i] == '-' && Process(P,i) == false)
		{
			P.insert(i , "(");
			for (int j = i + 2; j < P.length(); j++)
			{
				if ((P[j] < '0' || P[j] > '9') && P[j] != ')')
				{
					P.insert(j, ")");
					i = j;
					break;
				}
				if (j == P.length() - 1)
				{
					P.insert(j + 1, ")");
					i = j + 1;
					break;
				}
					
			}

		}
		if (P[i] == 'p')
		{
			if (isOperator(s1) == 1 || s1 == "p")
			{
				P.insert(P.begin() + i, '*');
				i++;
			}
		}
	}

	for (int i = 1; i < P.length(); i++)
	{
		if (P[i - 1] == '('&& P[i] == '-' && Process(P, i) == true)
		{
			P.erase(i-1, 1);
			P[i-1] = '#';
			for (int j = i; j < P.length(); j++)
			{
				if (P[j] == ')')
				{
					P.erase(j, 1);
					break;
				}					
			}
		}
	}
}

bool Checkvalid(string P)
{
	Xuli(P);

	int dem = 0;

	for (int i = 0; i < P.length() ; i++)
	{
		string s1(1, P[i]);

		if (isOperator(s1) == 1)
		{
			if (!((P[i] >= '0' && P[i] <= '9') || P[i] == 'p' || P[i] == '.'))
				return false;
		}

		else if (P[i] == '(' && P[i+1] == ')')
			return false;
		if (s1 == "(")
			dem++;
		else if (s1 == ")")
			dem--;
	}

	return (dem == 0);
}

void infix_to_postfix(string P, queue<string> &Q)
{
	stack <string> S;

	string s1;
	for (int i = 0; i < P.length(); i++)
	{
		string s(1, P[i]);
		if (isOperator(s) == 1)
		{
			if (s == "p")
			{
				Q.push(s);
			}
			else
			{
				s1 += s;
				string s2(1, P[i + 1]);
				if (s2 == ".")
				{
					s1 += s2;
					i++;
				}
				else if (isOperator(s2) != 1 || i == P.length() - 1)
				{
					Q.push(s1);
					s1 = "";
				}
			}
			
		}

		else if (isOperator(s) == 2)
		{
			if (!S.empty())
			{
				while (Priority(S.top()) >= Priority(s))
				{
					Q.push(S.top());
					S.pop();
					if (S.empty())
						break;
				}
			}
			S.push(s);
		}

		else if (s == "(")
		{
			S.push(s);
		}
		else if (s == ")")
		{
			while (S.top() != "(")
			{
				Q.push(S.top());
				S.pop();
			}
			S.pop();
		}
	}

	while (!S.empty())
	{
		Q.push(S.top());
		S.pop();
	}
}

double Expression_value(queue<string>& Q)
{
	double value = 0;
	stack <double> S;

	const double p = 3.141592654;

	while (!Q.empty())
	{

		if (isOperator(Q.front()) == 1)
		{
			if (Q.front() == "p")
			{
				S.push(p);
				Q.pop();
			}
			else
			{
				stringstream ss(Q.front());
				double n;
				ss >> n;
				S.push(n);
				Q.pop();
			}
		}

		else if (isOperator(Q.front()) != 1)
		{
			if (S.size() < 2 && Q.front() != "#")
			{
				cout << "Expression invalid" << endl;
				return 0;
			}
			else
			{
				if (Q.front() == "#")
				{
					double x = S.top();
					S.pop();
					x = -x;
					S.push(x);
				}
				else
				{
					double x = S.top();
					S.pop();
					double y = S.top();
					S.pop();
					double z;


					if (Q.front() == "+")
					{
						z = x + y;
						S.push(z);
					}
					if (Q.front() == "-")
					{
						z = y - x;
						S.push(z);
					}
					if (Q.front() == "*")
					{
						z = x * y;
						S.push(z);
					}
					if (Q.front() == "/")
					{
						z = y / x;
						S.push(z);
					}
					if (Q.front() == "^")
					{
						z = pow(y, x);
						S.push(z);
					}
				}
			}
				
			Q.pop();
		}
	}

	if (S.size() == 1)
	{
		value = S.top();
		S.pop();
	}

	else if(S.size() != 1)
	{
		cout << "Expression invalid" << endl;
		return 0;
	}

	return value;
}

double Calculate(string P)
{
	queue<string> Q;

	infix_to_postfix(P, Q);

	double value =  Expression_value(Q);
	
	return value;
}




