#include "node.h"
using namespace std;
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& oper, shared_ptr<Node> _left, shared_ptr<Node> _right) {
    op = oper;
    left = _left;
    right = _right;
}

DateComparisonNode::DateComparisonNode(const Comparison& comp, const Date& dat) {
    cmp = comp;
    date = dat;
}

EventComparisonNode::EventComparisonNode(const Comparison& comp, const string& ev) {
    cmp = comp;
    event = ev;
}

EmptyNode::EmptyNode() {};

//bool Node::Evaluate(const Date& dat, const string& ev) const { return true; };

bool LogicalOperationNode::Evaluate(const Date& dat, const string& ev) const /*override*/ {
    if(op == LogicalOperation::And) {
        return left -> Evaluate(dat, ev) && right -> Evaluate(dat, ev);
    } else {
        return left -> Evaluate(dat, ev) || right -> Evaluate(dat, ev);
    }
}

bool DateComparisonNode::Evaluate(const Date& dat, const string& ev) const /*override*/ {
    if(cmp == Comparison::Equal) {
		return dat == date;
    } else if(cmp == Comparison::NotEqual) {
		return dat != date; 
    } else if(cmp == Comparison::Greater) {
		return dat > date;
    } else if(cmp == Comparison::GreaterOrEqual) {
		return dat >= date;
    } else if(cmp == Comparison::Less) {
        return dat < date;
    } else if(cmp == Comparison::LessOrEqual) {
        return dat <= date;
	} else {
		return false;
	}
}

bool EventComparisonNode::Evaluate(const Date& dat, const string& ev) const /*override*/ {
	if (cmp == Comparison::Equal) {
		return ev == event;
	}
	else if (cmp == Comparison::NotEqual) {
		return ev != event;
	}
	else if (cmp == Comparison::Greater) {
		return ev > event;
	}
	else if (cmp == Comparison::GreaterOrEqual) {
		return ev >= event;
	}
	else if (cmp == Comparison::Less) {
		return ev < event;
	}
	else if (cmp == Comparison::LessOrEqual) {
		return ev <= event;
	}
	else {
		return false;
	}
}

bool EmptyNode::Evaluate(const Date& dat, const string& ev) const /*override*/ {
    return true;
}
