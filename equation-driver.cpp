#include <iostream>
#include <sstream>
#include "equation.h"

int main()
{
  string eqnstr;
  getline(cin, eqnstr);
  while (eqnstr != "quit")
  {
    try
    {
      Equation eq(eqnstr);
      cout << eq.evaluate() << endl;
    }
    catch (exception* ex)
    {
      cout << ex->what() << endl;
      delete ex;
    }
    getline(cin, eqnstr);
  }

  return 0;
}