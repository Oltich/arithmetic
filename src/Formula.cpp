#include "Formula.h"
#include <stdexcept>

TFormula::TFormula(const std::string& expr) : infix(expr), postfix(""), opStack(MaxLength), valStack(MaxLength) {}

void TFormula::SetFormula(const std::string& expr) {
  infix = expr;
  postfix = "";
}

bool TFormula::IsOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int TFormula::Priority(char op) {
  switch (op) {
  case '+':
  case '-': return 1;
  case '*':
  case '/': return 2;
  default: return 0;
  }
}

bool TFormula::CheckBrackets() {
  TStack<char> s(MaxLength);
  for (char c : infix) {
    if (c == '(') s.Push(c);
    else if (c == ')') {
      if (s.IsEmpty()) return false;
      s.Pop();
    }
  }
  return s.IsEmpty();
}

void TFormula::ToPostfix() {
  postfix.clear();
  for (size_t i = 0; i < infix.length(); i++) {
    char c = infix[i];

    if (isspace(c)) continue;

    if (isdigit(c) || c == '.') {
      while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
        postfix += infix[i++];
      }
      postfix += ' ';
      i--;
    }
    else if (c == '(') {
      opStack.Push(c);
    }
    else if (c == ')') {
      while (!opStack.IsEmpty() && opStack.Top() != '(') {
        postfix += opStack.Pop();
        postfix += ' ';
      }
      if (!opStack.IsEmpty()) opStack.Pop();
    }
    else if (IsOperator(c)) {
      while (!opStack.IsEmpty() && Priority(opStack.Top()) >= Priority(c)) {
        postfix += opStack.Pop();
        postfix += ' ';
      }
      opStack.Push(c);
    }
  }

  while (!opStack.IsEmpty()) {
    postfix += opStack.Pop();
    postfix += ' ';
  }
}

std::string TFormula::ConvertToPostfix() {
  if (!CheckBrackets()) {
    throw std::invalid_argument("Mismatched brackets in expression");
  }
  ToPostfix();
  return postfix;
}

double TFormula::CalculatePostfix() {
  std::istringstream iss(postfix);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
      valStack.Push(std::stod(token));
    }
    else if (IsOperator(token[0])) {
      if (valStack.IsEmpty()) throw std::runtime_error("Invalid expression");
      double b = valStack.Pop();
      if (valStack.IsEmpty()) throw std::runtime_error("Invalid expression");
      double a = valStack.Pop();
      double result = 0;
      switch (token[0]) {
      case '+': result = a + b; break;
      case '-': result = a - b; break;
      case '*': result = a * b; break;
      case '/':
        if (b == 0) throw std::runtime_error("Division by zero");
        result = a / b;
        break;
      }
      valStack.Push(result);
    }
  }
  if (valStack.IsEmpty()) throw std::runtime_error("No result");
  return valStack.Pop();
}

double TFormula::Calculate() {
  ConvertToPostfix();
  return CalculatePostfix();
}