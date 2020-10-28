#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	//каждый символ должен быть разделён от последующего ровно одним пробелом!
  TPostfix postfix("a + d / cos ( u - r )");
  double res;

  setlocale(LC_ALL, "Russian");

  cout << " Арифметическое выражение: " << postfix.GetInfix() << endl;
  cout << " Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << " Результат = "<< res << endl;
  return 0;
}
