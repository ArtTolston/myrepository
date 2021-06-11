#pragma once
#include "node.h"
#include <memory>
#include <iostream>
#include "token.h"
using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
void TestDbAdd();
void TestDbFind();
void TestDbLast();
void TestDbRemoveIf();
void TestParseDate();
void TestNodes();
void TestDatabase2();