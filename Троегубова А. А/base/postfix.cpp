#include "postfix.h"

TPostfix::TPostfix()
{
	infix = "a + b";
	postfix = "a b +";
}

TPostfix::TPostfix(string exp)
{
	infix = exp;
	ToPostfix();
}

string TPostfix::GetInfix()
{
	return infix;
}

string TPostfix::GetPostfix()
{
	return postfix;
}

vector<string> TPostfix::Сonvert(string exp)
{
	string symbol;
	stringstream ss(exp);
	vector <string> res;
	while (ss >> symbol)
		res.push_back(symbol);
	return res;
}

vector<int> TPostfix::PositionOfBrackets(vector<string> exp)
{//поиск позиций скобок в выражении
	TStack<string> pos(exp.size() / 2);
	int pos1, pos2;
	pos1 = pos2 = -1;
	vector<int> res;
	string tmp;
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == "(")
		{
			if (pos.IsEmpty()) pos1 = i;
			pos.Put("(");

		}
		if (exp[i] == ")")
		{
			tmp = pos.Get();
			pos2 = i;
		}
		if (pos.IsEmpty() && (pos1 != -1))
		{
			return { pos1, pos2 };
		}
	}
	return { pos1, pos2 };//если в выражении нет скобок, то возвр -1
}

vector<string> TPostfix::VectorSegment(vector<string> exp, int ix)//возращает подстроку строки, начиная с ix - индекса и до конца
{
	vector<string> res;

	vector<string>::iterator first = exp.begin(), last = exp.end();

	advance(first, ix);// advance(last, exp.size() - 1);
	std::copy(first, last, std::back_inserter(res));
	return res;
}

vector<string> TPostfix::VectorSegmentInBrackets(vector<string> exp)
{//копирует выражение в скобках
	vector<int> pos = PositionOfBrackets(exp);
	vector<string> res;

	vector<string>::iterator first = exp.begin(), last = exp.begin();

	advance(first, pos[0] + 1); advance(last, pos[1]);
	std::copy(first, last, std::back_inserter(res));
	return res;
}

vector<string> TPostfix::CheckingTheCorrectness(vector<string> exp)
{
	TStack<string> brackets(exp.size() / 2);
	string tmp;
	for (int i = 0; i < exp.size(); i++)
	{
		if (exp[i] == "(")
			brackets.Put("(");
		if (exp[i] == ")")
		{
			if (brackets.IsEmpty())
				throw "invalid expression";
			tmp = brackets.Get();
		}
			
	}
	if (!brackets.IsEmpty())
		throw "invalid expression";

	if ((exp[0] == "*") || (exp[0] == "/") || (exp[0] == "^")) 
		throw "invalid expression";

	for (int i = 0; i < exp.size() - 1; i++)
	{
		if ((operation.find(exp[i]) == operation.end()) && (operation.find(exp[i + 1]) == operation.end()))
			throw "invalid expression";

		if ((exp[i] == "(") && (exp[i + 1] == ")"))
			throw "invalid expression";

		if ((exp[i] == "-") && (exp[i + 1] == "-"))
		{
			exp[i + 1] = "+";
			exp.erase(exp.begin() + i);
			i -= 1;
		}
		else
		{
			if (((exp[i] == "-") && (exp[i + 1] == "+")) || ((exp[i] == "+") && (exp[i + 1] == "-")))
			{
				exp[i + 1] = "-";
				exp.erase(exp.begin() + i);
				i -= 1;
			}
			else
			{
				if ((operation.find(exp[i]) != operation.end() && (operation.find(exp[i + 1]) != operation.end())))
				{
					if ((operation.find(exp[i]) -> second.second == 2) && (operation.find(exp[i + 1])->second.second == 2))
						throw "invalid expression";
				}

				if ((operation.find(exp[i])->second.second == 1) && (exp[i + 1] != "("))
					throw "invalid expression";

				if (exp[i] == "(")
				{
					if ((exp[i + 1] == "*") || (exp[i + 1] == "/") || (exp[i + 1] == "^"))
						throw "invalid expression";
				}

				if ((operation.find(exp[i]) != operation.end()) && (exp[i] != ")") && (exp[i + 1] == ")"))
					throw "invalid expression";
			}
		}
		
	}
	return exp;
}

void TPostfix::ToPostfix()//infix -> postfix
{
	vector<string> converted_infix = Сonvert(infix);
	postfix = Support(CheckingTheCorrectness(converted_infix));
}

string TPostfix::Support(vector<string> exp)
{
	TStack<string> operation_stack((exp.size() / 2) + 1);
	string res, tmp1;
	int flag = 0;
	map <string, pair<int, int>> ::iterator it;

	for (int i = 0; i < exp.size(); i++)
	{
		flag = 0;
		for (it = operation.begin(); it != operation.end(); it++)
		{

			if (exp[i] == it->first)//ищем операцию
			{
				flag = 1;
				switch (it->second.first)
				{
				case(0):
				{
					//написать метод возращающий копию сроки от определённого индекса
					res += Support(VectorSegmentInBrackets(VectorSegment(exp, i)));
					i += PositionOfBrackets(VectorSegment(exp, i))[1];
					break;
				}
				case(1):
					break;
				case(2):
				{
					res += Support(VectorSegmentInBrackets(VectorSegment(exp, i))) + exp[i] + " ";
					i += PositionOfBrackets(VectorSegment(exp, i))[1];
					break;
				}
				default:
					int count = operation_stack.Cardinality();
					for (int j = 0; j < count; j++)
					{
						if (operation.find(operation_stack.Head())->second.first <= it->second.first)//сравниваем приоритеты предыдущей и текущей операции 
						{
							res += operation_stack.Get() + " ";
						}
					}
					operation_stack.Put(exp[i]);
				}
			}
		}
		if (flag == 0)
			res += exp[i] + " ";
	}
	int count = operation_stack.Cardinality();

	for (int i = 0; i < count; i++)
		res += operation_stack.Get() + " ";
	return res;
}

double TPostfix::Calculate()
{
	vector<string> exp1 = Сonvert(infix);
	map<string, double> variable;
	double tmp;
	double res = 0;
	cout << infix << endl;

	for (int i = 0; i < exp1.size(); i++)
	{
		if ((operation.find(exp1[i]) == operation.end()) && (variable.find(exp1[i]) == variable.end()) && (constants.find(exp1[i]) == constants.end()))
		{
			cout << " " << exp1[i] << "  =  ";
			cin >> tmp;
			variable[exp1[i]] = tmp;
		}
	}

	map <string, double> ::iterator it1;
	map <string, pair<int, int>> ::iterator it2;
	exp1 = Сonvert(postfix);
	TStack<double> var(exp1.size());

	for (int i = 0; i < exp1.size(); i++)
	{
		if (operation.find(exp1[i]) == operation.end())//переменная или константа?
		{
			if (variable.find(exp1[i]) != variable.end())//переменная?
			{
				it1 = variable.find(exp1[i]);
				var.Put(it1->second);
			}
			else//константа
			{
				it1 = constants.find(exp1[i]);
				var.Put(it1->second);
			}
		}
		else
		{
			it2 = operation.find(exp1[i]);
			if (it2->first == "+")
			{
				res = var.Get() + var.Get();
				var.Put(res);
			}
			if (it2->first == "-") //возможность посчитать выражение вида - a + b
			{
				if (var.Cardinality() == 1)
					res = 0 - var.Get();
				else
				{
					tmp = var.Get();
					res = var.Get() - tmp;
				}
				var.Put(res);
			}
			if (it2->first == "*")
			{
				res = var.Get() * var.Get();
				var.Put(res);
			}
			if (it2->first == "/")
			{
				tmp = var.Get();
				res = var.Get() / tmp;
				var.Put(res);
			}
			if (it2->first == "^")
			{
				tmp = var.Get();
				res = pow(var.Get(), tmp);
				var.Put(res);
			}
			if (it2->first == "cos")
			{
				res = cos(var.Get());
				var.Put(res);
			}
			if (it2->first == "sin")
			{
				res = sin(var.Get());
				var.Put(res);
			}
			if (it2->first == "tg")
			{
				res = tan(var.Get());
				var.Put(res);
			}
			if (it2->first == "ctg")
			{
				res = 1 / tan(var.Get());
				var.Put(res);
			}
			if (it2->first == "ln")
			{
				res = log(var.Get());
				var.Put(res);
			}
			if (it2->first == "exp")
			{
				res = exp(var.Get());
				var.Put(res);
			}
		}
	}
	return res;
}


