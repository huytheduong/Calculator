#include <sstream>
#include "equation.h"
#include <iostream>
#include <string>
// static variable
unordered_map<string, int> Variable::vars;

// Constant and Variable classes
Constant::Constant(int val)
{
    value = val;
}

int Constant::getValue() const
{
    return value;
}

Variable::Variable(string line)
{
    name = line;
}

int Variable::getValue() const
{
    unordered_map<string, int>::iterator it = vars.find(name);
    if (it != vars.end())
        return it->second;
    else
        throw new UninitializedVariableException();
}

void Variable::setValue(int value)
{
    // variables stored here only when they receive values
    vars[name] = value;
}

//Equation class
Equation::Equation(string line)
{
    var = nullptr;
    lhs = nullptr;
    rhs = nullptr;

    bool isBad = false;

    try
    {
        istringstream iss(line);

        iss >> &var; // extract the left part

        // extract = sign
        string equal;
        iss >> equal;
        if (equal != "=")
            isBad = true;

        iss >> &lhs; // extract the first operand

        iss >> &op ; // extract the operator

        iss >> &rhs; // extract the second operand
    }
    catch (BadEquationException&)
    {
        isBad = true;
    }

    if (isBad)
    {

        throw new BadEquationException();
    }
}

Equation::~Equation()
{
    if(var != nullptr)
        delete var;
    if (lhs != nullptr)
        delete lhs;
    if (rhs != nullptr)
        delete rhs;

}


int Equation::evaluate()
{
    // operand values
    int val1 = lhs->getValue(), val2 = rhs->getValue();

    // and operation
    int result = 0;
    if (op == PLUS_OPERATOR)
        result = val1 + val2;
    else if (op == MINUS_OPERATOR)
        result = val1 - val2;
    else if (op == TIMES_OPERATOR)
        result = val1 * val2;
    else if (op == DIV_OPERATOR)
        result = val1 / val2;
    else if (op == MOD_OPERATOR)
        result = val1 % val2;
    else
        throw new BadOperatorException();

    var->setValue(result);

    return result;
}

//Extraction operators
istream& operator>>(istream& in, Variable** v)
{
    string varstr;
    in >> varstr;

    bool isBad = (varstr == "");
    if (!isBad) // name must start from a letter
        isBad = !isalpha(varstr[0]);

    if(isBad)
        throw new BadEquationException();

    *v = new Variable(varstr);

    return in;
}

istream& operator>>(istream& in, operator_t* op)
{
    string opstr;
    in >> opstr;

    if (opstr == "+")
        *op = PLUS_OPERATOR;
    else if (opstr == "-")
        *op = MINUS_OPERATOR;
    else if (opstr == "*")
        *op = TIMES_OPERATOR;
    else if (opstr == "/")
        *op = DIV_OPERATOR;
    else if (opstr == "%")
        *op = MOD_OPERATOR;
    else
        *op = INVALID_OPERATOR;

    return in;
}

istream& operator>>(istream& in, Operand** o)
{
    string varstr;
    in >> varstr;

    if (varstr == "")
        throw new BadEquationException();

    bool isNum = true;
    int num;
    try
    {
        num = stoi(varstr);
    }
    catch (exception e)
    {
        isNum = false;
    }

    if(isNum)
        *o = new Constant(num);
    else
    {
        if(!isalpha(varstr[0])) // name must start from a letter
            throw new BadEquationException();

        *o = new Variable(varstr);
    }

    return in;
}
