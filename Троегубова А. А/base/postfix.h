#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include<map>
#include <iostream>
#include <utility>
#include <string>
#include<vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	map<string, pair<int, int>> operation = { {"(", make_pair(0,0)}, {")",make_pair(1,0)}, {"sin",make_pair(2,1)}, {"cos",make_pair(2,1)}, {"tg",make_pair(2,1)}, {"ctg",make_pair(2,1)},
					  {"exp",make_pair(2,1)}, {"ln",make_pair(2,1)}, {"^",make_pair(3,2)}, {"*",make_pair(4,2)}, {"/", make_pair(4,2)}, {"+", make_pair(5,2)},  {"-",make_pair(5,2)} };
	//fist - приоритет; second - кол-во операндов

	vector<string> Сonvert(string exp);
	vector<int> PositionOfBrackets(vector<string> exp);
	vector<string> VectorSegment(vector<string> exp, int ix);
	vector<string> VectorSegmentInBrackets(vector<string> exp);
	string Support(vector<string> exp);
	void ToPostfix();
public:
	TPostfix();
	TPostfix(string exp);
	string GetInfix();
	string GetPostfix();
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif