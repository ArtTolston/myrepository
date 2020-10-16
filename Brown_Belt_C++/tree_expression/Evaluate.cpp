#include"Common.h"


ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
	return make_unique<Operator>(left, right);
}

ExpressionPtr Value(int value) {
	return make_unique<Operand>(value);
}