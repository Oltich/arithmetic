#pragma once

#include <string>
#include <sstream>
#include <cmath>
#include "Stack.h"

const int MaxLength = 255;

class TFormula {
private:
  std::string infix;
  std::string postfix;
  TStack<char> opStack;
  TStack<double> valStack;

  bool IsOperator(char c);
  int Priority(char op);
  void ToPostfix();
  double CalculatePostfix();

public:
  TFormula(const std::string& expr = "");
  ~TFormula() {}

  void SetFormula(const std::string& expr);
  std::string GetPostfix() const { return postfix; }

  bool CheckBrackets();
  std::string ConvertToPostfix();
  double Calculate();
};
