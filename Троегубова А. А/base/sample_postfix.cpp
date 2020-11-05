#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;


int main()
{
  setlocale(LC_ALL, "Russian");
  string exp;
  int r = 0;
  while (true)
  {
	  system("cls");
	  cout << " 1. Каждая переменная или константа должена быть разделёна от операции ровно одним пробелом!" << endl <<
		  " 2. Операции также должны быть разделены друг от друга ровно одним пробелом." << endl <<
		  " 3. Mожно использовать константы pi и e." << endl <<
		  " 4. Аргумант унарных операций указывается в скобках." << endl <<
		  " Введите арифметическое выражение:  ";
	  if (r == 0)
		  getline(cin, exp);
	  else
	  {
		  getline(std::cin, exp);
		  getline(std::cin, exp);
	  }
	  TPostfix postfix(exp);
	  double res;
	  cout << " Арифметическое выражение: " << postfix.GetInfix() << endl;
	  cout << " Постфиксная форма: " << postfix.GetPostfix() << endl;
	  res = postfix.Calculate();
	  cout << " Результат = " << res << endl;
	  cout << " Продолжить работу программы? " << endl << " 1)да " << endl << " 2)нет" << endl;
	  std::cin >> r;
	  if (r != 1) break;
  }
  return 0;
}
