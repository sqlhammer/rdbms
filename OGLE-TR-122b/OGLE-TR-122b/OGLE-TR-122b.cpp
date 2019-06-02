// OGLE-TR-122b.cpp : This file contains the 'main' function. Program execution begins and ends there.
// OGLE-TR-112b is the smallest known star in our galaxy, like this project which is the smallest RDBMS which can be made.

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

#include "global.h"
#include "results.h"
#include "types.h"
#include "Row.h"
#include "Statement.h"
#include "Table.h"
#include "parser.h"
#include "userinterface.h"
#include "pager.h"
#include "btree.h"

using namespace std;

const string version = "0.1";

int main()
{
	Table t;
	
	UserInterface::print_header(version);
	UserInterface::REPL(&t);
}
