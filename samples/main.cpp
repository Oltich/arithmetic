#include <iostream>
#include "Formula.h"
#include <windows.h>

int main() {
  setlocale(LC_ALL, "Russian");

  std::string expressions[] = {
      "1+2",
      "1+2*(3-2)-4",
      "(((1+23)*1-22)+5)*2-(7",
      "1+2/(3-3)",
      "1++1"
  };

  for (const auto& expr : expressions) {
    std::cout << "\nВыражение: " << expr << std::endl;
    TFormula formula(expr);

    if (!formula.CheckBrackets()) {
      std::cout << "Ошибок: 1 (скобки)" << std::endl;
      std::cout << "Перевод и вычисление невозможны" << std::endl;
      continue;
    }
    std::cout << "Ошибок: 0" << std::endl;

    try {
      std::string postfix = formula.ConvertToPostfix();
      std::cout << "Постфиксная форма: " << postfix << std::endl;

      double result = formula.Calculate();
      std::cout << "Результат: " << result << std::endl;
    }
    catch (const std::exception& e) {
      std::cout << "Ошибка вычисления: " << e.what() << std::endl;
    }
  }

  return 0;
}