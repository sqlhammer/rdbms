// OGLE-TR-122b.cpp : This file contains the 'main' function. Program execution begins and ends there.
// OGLE-TR-112b is the smallest known star in our galaxy, like this project which is the smallest RDBMS which can be made.

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "results.h"
#include "types.h"
#include "parser.h"
#include "userinterface.h"

using namespace std;

const string version = "0.1";

int main()
{
	UserInterface::print_header(version);
	UserInterface::REPL();

}
