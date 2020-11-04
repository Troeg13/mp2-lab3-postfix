#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

//каждая переменная или константа должена быть разделёна от операции ровно одним пробелом!;
//операции также должны быть разделены друг от друга ровно одним пробелом
//можно использовать константы pi и e
//можно добавить свою константу и использовать её
//аргумант унарных операций указывается в скобках

int main()
{
  setlocale(LC_ALL, "Russian");
  TPostfix postfix("- cos ( pi / a ) + b");
  double res;
  cout << " Арифметическое выражение: " << postfix.GetInfix() << endl;
  cout << " Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << " Результат = "<< res << endl;
  return 0;
}
