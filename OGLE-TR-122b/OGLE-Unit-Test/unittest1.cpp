#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

#include "../OGLE-TR-122b/global.h"
#include "../OGLE-TR-122b/results.h"
#include "../OGLE-TR-122b/types.h"
#include "../OGLE-TR-122b/Row.h"
#include "../OGLE-TR-122b/Statement.h"
#include "../OGLE-TR-122b/Table.h"
#include "../OGLE-TR-122b/parser.h"
#include "../OGLE-TR-122b/userinterface.h"
#include "../OGLE-TR-122b/pager.h"
#include "../OGLE-TR-122b/btree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OGLEUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(insert_row)
		{
			//Setup
			Table table;
			string input = "insert 1 str1 str2";

			//Execute
			Parser::parse_execute(&input, &table);

			//Assert
			Row row;
			row.deserialize_row((char*)Parser::row_slot(&table, 0), &row);

			Assert::AreEqual(row.id, 1);
			Assert::AreEqual(row.username, "str1");
			Assert::AreEqual(row.email, "str2");
		}

		TEST_METHOD(select_single_row)
		{
			//Setup
			Table table;
			
			string input = "insert 1 str1 str2";
			Parser::parse_execute(&input, &table);

			Statement statement;
			statement.text = "select";
			statement.type = Types::STATEMENT_SELECT;

			//Execute
			ExecuteResult result = Parser::execute_select(&statement, &table);

			//Assert
			Global g;
			int enum_int = g.as_integer(ExecuteResult::EXECUTE_SUCCESS);
			int result_int = g.as_integer(result);
			Assert::AreEqual(result_int,enum_int);
		}

	};
}