#include <gtest.h>
#include "Stack.h"
#include "Formula.h"


TEST(TStackTest, ConstructorAndIsEmpty) {
  TStack<int> stack(5);
  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_FALSE(stack.IsFull());
}

TEST(TStackTest, PushAndTop) {
  TStack<int> stack(3);
  stack.Push(10);
  EXPECT_EQ(stack.Top(), 10);
  stack.Push(20);
  EXPECT_EQ(stack.Top(), 20);
  EXPECT_FALSE(stack.IsEmpty());
}

TEST(TStackTest, PushAndPop) {
  TStack<int> stack(3);
  stack.Push(10);
  stack.Push(20);
  stack.Push(30);
  EXPECT_EQ(stack.Pop(), 30);
  EXPECT_EQ(stack.Pop(), 20);
  EXPECT_EQ(stack.Pop(), 10);
  EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStackTest, StackOverflow) {
  TStack<int> stack(2);
  stack.Push(1);
  stack.Push(2);
  EXPECT_THROW(stack.Push(3), std::overflow_error);
}

TEST(TStackTest, EmptyStackPopTop) {
  TStack<int> stack(3);
  EXPECT_THROW(stack.Pop(), std::underflow_error);
  EXPECT_THROW(stack.Top(), std::underflow_error);
}

TEST(TFormulaTest, CheckBracketsCorrect) {
  TFormula f1("(1+2)");
  EXPECT_TRUE(f1.CheckBrackets());

  TFormula f2("((1+2)*(3-4))");
  EXPECT_TRUE(f2.CheckBrackets());

  TFormula f3("1+2");
  EXPECT_TRUE(f3.CheckBrackets());
}

TEST(TFormulaTest, CheckBracketsIncorrect) {
  TFormula f1("(1+2");
  EXPECT_FALSE(f1.CheckBrackets());

  TFormula f2("1+2)");
  EXPECT_FALSE(f2.CheckBrackets());

  TFormula f3("((1+2)*3))");
  EXPECT_FALSE(f3.CheckBrackets());
}

TEST(TFormulaTest, ConvertToPostfix) {
  TFormula f1("1+2");
  EXPECT_EQ(f1.ConvertToPostfix(), "1 2 + ");

  TFormula f2("1+2*3");
  EXPECT_EQ(f2.ConvertToPostfix(), "1 2 3 * + ");

  TFormula f3("(1+2)*3");
  EXPECT_EQ(f3.ConvertToPostfix(), "1 2 + 3 * ");
}

TEST(TFormulaTest, CalculateSimple) {
  TFormula f1("1+2");
  EXPECT_DOUBLE_EQ(f1.Calculate(), 3.0);

  TFormula f2("10-4");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 6.0);

  TFormula f3("2*3");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 6.0);

  TFormula f4("10/2");
  EXPECT_DOUBLE_EQ(f4.Calculate(), 5.0);
}

TEST(TFormulaTest, CalculateComplex) {
  TFormula f1("(1+2)*(3-4)");
  EXPECT_DOUBLE_EQ(f1.Calculate(), -3.0);

  TFormula f2("(10+5)/3");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 5.0);

  TFormula f3("2+3*4-10/2");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 9.0);
}

TEST(TFormulaTest, ErrorHandling) {
  TFormula f1("1/0");
  EXPECT_THROW(f1.Calculate(), std::runtime_error);

  TFormula f2("(1+2");
  EXPECT_THROW(f2.ConvertToPostfix(), std::invalid_argument);

  TFormula f3("1++1");
  EXPECT_THROW(f3.Calculate(), std::runtime_error);

  TFormula f4("");
  EXPECT_THROW(f4.Calculate(), std::runtime_error);
}

TEST(TFormulaTest, FloatingPointNumbers) {
  TFormula f1("1.5+2.5");
  EXPECT_DOUBLE_EQ(f1.Calculate(), 4.0);

  TFormula f2("3.14*2");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 6.28);

  TFormula f3("10.5/2.5");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 4.2);
}

TEST(TFormulaTest, OperatorPrecedence) {
  TFormula f1("1+2*3");
  EXPECT_DOUBLE_EQ(f1.Calculate(), 7.0);

  TFormula f2("(1+2)*3");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 9.0);

  TFormula f3("10/2*5");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 25.0);

  TFormula f4("10+2*3-4/2");
  EXPECT_DOUBLE_EQ(f4.Calculate(), 14.0);
}

TEST(TFormulaTest, NegativeNumbersBinary) {
  TFormula f1("5-10");
  EXPECT_DOUBLE_EQ(f1.Calculate(), -5.0);

  TFormula f2("3+(2-5)");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 0.0);

  TFormula f3("0-5");
  EXPECT_DOUBLE_EQ(f3.Calculate(), -5.0);
}

TEST(TFormulaTest, NestedBrackets) {
  TFormula f1("(((1+2)*3)-4)/5");
  EXPECT_DOUBLE_EQ(f1.Calculate(), 1.0);

  TFormula f2("((2+3)*(4-1))/2");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 7.5); 

  TFormula f3("(2*(3+4))-5");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 9.0);
}

TEST(TFormulaTest, PostfixForComplexExpressions) {
  TFormula f1("(a+b)*(c-d)");
  SUCCEED();
}

TEST(TFormulaTest, SpacesInExpression) {
  TFormula f1(" 1 + 2 ");
  EXPECT_DOUBLE_EQ(f1.Calculate(), 3.0);

  TFormula f2("( 1 + 2 ) * 3 ");
  EXPECT_DOUBLE_EQ(f2.Calculate(), 9.0);

  TFormula f3("10 / 2 + 3 * 4");
  EXPECT_DOUBLE_EQ(f3.Calculate(), 17.0); // 5 + 12 = 17
}
