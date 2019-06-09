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

			Row* rows = NULL;
			rows = new Row[table.number_of_rows];

			//Execute
			rows = Parser::get_rows_for_select(&statement, &table);

			//Assert
			Assert::AreEqual(rows[0].id,1);
			Assert::AreEqual(rows[0].username, "str1");
			Assert::AreEqual(rows[0].email, "str2");
		}

		TEST_METHOD(table_full)
		{
			//Setup
			Global g;
			Table table;
			int rows_to_insert = 2801;

			Statement statement;
			statement.text = "insert 1 str1 str2";
			statement.type = Types::STATEMENT_INSERT;
			
			ExecuteResult result;
			int int_expected = g.as_integer(ExecuteResult::EXECUTE_TABLE_FULL);
			int int_result = 0;
			
			//Execute
			for (int i = 0; i < rows_to_insert; i++)
			{
				result = Parser::execute_statement(&statement, &table);
				int_result = g.as_integer(result);

				if (int_result == int_expected)
				{
					break;
				}
			}

			//Assert			
			Assert::AreEqual(int_result, int_expected);
		}

		TEST_METHOD(insert_correct_column_lengths)
		{
			//Setup
			Global g;
			Table table;

			Statement statement;
			statement.text = "insert 1 " + string(statement.row.COLUMN_USERNAME_SIZE, 'a') + " " + string(statement.row.COLUMN_USERNAME_SIZE, 'a');
			statement.type = Types::STATEMENT_INSERT;

			ExecuteResult result;
			int int_expected = g.as_integer(ExecuteResult::EXECUTE_SUCCESS);
			int int_result = 0;

			//Execute
			result = Parser::execute_statement(&statement, &table);

			//Assert			
			int_result = g.as_integer(result);
			Assert::AreEqual(int_result, int_expected);
		}

		TEST_METHOD(insert_incorrect_column_lengths)
		{
			//Setup
			Global g;
			Table table;

			Statement statement;
			statement.text = "insert 1 " + string(statement.row.COLUMN_USERNAME_SIZE + 1, 'a') + " " + string(statement.row.COLUMN_USERNAME_SIZE + 1, 'a');
			statement.type = Types::STATEMENT_INSERT;

			PrepareResult result;
			int int_expected = g.as_integer(PrepareResult::PREPARE_SYNTAX_ERROR);
			int int_result = 0;

			//Execute
			result = Parser::prepare_sql_statement(&statement);

			//Assert			
			int_result = g.as_integer(result);
			Assert::AreEqual(int_result, int_expected);
		}

	};
}