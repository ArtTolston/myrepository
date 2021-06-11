#pragma once
#include "date.h"
#include <string>
#include <memory>
using namespace std;
enum class Comparison {
    Less,
    LessOrEqual,
    Equal,
    Greater,
    GreaterOrEqual,
    NotEqual,
};

enum class LogicalOperation {
    Or,
    And,
};

class Node {
public:
    virtual bool Evaluate(const Date& dat, const string& ev) const = 0;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& comp, const Date& dat);
    bool Evaluate(const Date& dat, const string& ev) const override;
private:
    Comparison cmp;
    Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& comp, const string& ev);
    bool Evaluate(const Date& dat, const string& ev) const override;
private:
    Comparison cmp;
    string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& oper, shared_ptr<Node> _left, shared_ptr<Node> _right);
    bool Evaluate(const Date& dat, const string& ev) const override;
private:
    LogicalOperation op;
    shared_ptr<const Node> left, right;
};

class EmptyNode : public Node {
public:
	EmptyNode();
    bool Evaluate(const Date& dat, const string& ev) const override;
};
