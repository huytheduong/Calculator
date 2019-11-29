#ifndef __EQUATION_H
#define __EQUATION_H

#include <unordered_map>
using namespace std;

//Enum representing one of the operators +, -, *, /, and %
enum operator_t { PLUS_OPERATOR, MINUS_OPERATOR, TIMES_OPERATOR, DIV_OPERATOR, MOD_OPERATOR, INVALID_OPERATOR };

//Class representing a constant or variable
//Every equation has an operator and two operands on the right-hand side
class Operand {
public:
  //Returns the value of a constant or variable
  virtual int getValue() const = 0;
};

//Class representing an integer constant
class Constant : public Operand
{
private:
  int value;
public:
  //Constructs a constant with the given value
  Constant(int);
  //Returns the value of this constant
  virtual int getValue() const override;
};

//Class representing a variable
//Variable values are stored in the static map vars
class Variable : public Operand
{
private:
  static unordered_map<string, int> vars;
  string name;
public:
  //Constructs a variable with the given name
  Variable(string);
  //Returns the value of the variable
  //Throws UnititializedVariableException if not initialized
  virtual int getValue() const override;
  //Sets the value of this variable to the given value
  void setValue(int);
};

//Class representing an equation
//The left-hand side of an equation should be a variable, while the right-hand side should have an operator and two operands
class Equation
{
private:
  Variable* var;
  Operand* lhs;
  operator_t op;
  Operand* rhs;
public:
  //Creates an equation from the given line of input
  //Input should be in the form [variable] = [operand] [operator] [operand]
  //Throws BadEquationException if equation does not have all 5 parts
  Equation(string);
  //Performs the assignment the equation represents
  //Returns the value of the right-hand side
  //Throws BadOperatorException if the operator is invalid (INVALID_OPERATOR)
  int evaluate();
  //Destructor:  frees the variable and operands
  //Should also implement copy constructor and copy assignment (rule of three), but these are not used by main function
  ~Equation();
};

//Reads a variable from an input stream
//A variable should have a one-word name that does not start with a digit or minus sign
istream& operator>>(istream& in, Variable** v);
//Reads an operator from an input stream
//Valid operators:  +, -, *, /, %
istream& operator>>(istream& in, operator_t* op);
//Reads a variable or constant from an input stream
//Constants are integers, while variables should have names that do not start with a digit or minus sign
//Throws BadEquationException if we can't read an int or non-empty string
istream& operator>>(istream& in, Operand** o);

//Exception class for accessing uninitialized variables
class UninitializedVariableException : public exception
{
private:
  virtual const char* what() const noexcept { return "Variable is not initialized"; }
};

//Exception class for performing an undefined operation
class BadOperatorException : public exception
{
private:
  virtual const char* what() const noexcept { return "Your operator is invalid"; }
};

//Exception class for an invalid equation
class BadEquationException : public exception
{
private:
  virtual const char* what() const noexcept { return "The equation does not have 5 parts:  [variable] = [operand] [operator] [operand]"; }
};
#endif