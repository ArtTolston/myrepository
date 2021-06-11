#include "Common.h"
using namespace std;

enum class Operators {
	Addition,
	Multiplication
};

class Operand : public Expression {
public:
	Operand(const int& value);

	int Evaluate() const override;

	std::string ToString() const override;

private:
	int operand;
};

class Operator : public Expression {
public:
	Operator(ExpressionPtr left_, ExpressionPtr right_, Operators oper_);

	int Evaluate() const override;

	std::string ToString() const override;

private:
	ExpressionPtr left;
	ExpressionPtr right;
	Operators oper;
};

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
	return move(make_unique<Operator>(move(left), move(right), Operators::Multiplication));
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
	return move(make_unique<Operator>(move(left), move(right), Operators::Addition));
}

ExpressionPtr Value(int value) {
	return move(make_unique<Operand>(value));
}


// Operator's definitions   ////////////////////////////////////////////////////////////////////

Operator::Operator(ExpressionPtr left_, ExpressionPtr right_, Operators oper_) : left(move(left_)), right(move(right_)), oper(oper_) {}

int Operator::Evaluate() const
{
	if (oper == Operators::Addition) {
		return left->Evaluate() + right->Evaluate();
	}
	else {
		return left->Evaluate() * right->Evaluate();
	}
}

string Operator::ToString() const
{
	if (oper == Operators::Addition) {
		return "(" + left->ToString() + ")+(" + right->ToString() + ")";
	}
	else {
		return  "(" + left->ToString() + ")*(" + right->ToString() + ")" ;
	}
}


// Operand's definitions /////////////////////////////////////////////////////////

Operand::Operand(const int& value) : operand(value) {}

int Operand::Evaluate() const
{
	return operand;
}

string Operand::ToString() const
{
	return to_string(operand);
}
