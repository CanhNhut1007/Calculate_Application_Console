#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <sstream>
#include <cmath>
using namespace std;

void XuliKhoangTrang(string &P);

void Xuli(string &P);

bool Checkvalid(string P);

int Priority(string s);

int isOperator(string s);

void infix_to_postfix(string P, queue<string> &Q);

double Expression_value(queue<string> &Q);

double Calculate(string P);

