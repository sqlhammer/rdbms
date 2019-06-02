
using namespace std;

static class Parser
{
public:
	Parser() {};
	~Parser() {};

	static void* row_slot(Table* table, int row_num)
	{
		int page_num = row_num / (table->ROWS_PER_PAGE);
		char* page = (char*)table->pages[page_num];
		if (page == NULL)
		{
			// Allocate memory only when we try to access page
			page = (char*)(table->pages[page_num] = malloc(Global::PAGE_SIZE));
		}
		int row_offset = row_num % (table->ROWS_PER_PAGE);
		int byte_offset = row_offset * (table->ROW_SIZE);
		return page + byte_offset;
	}

	static void parse_execute(string* input, Table* table)
	{
		std::transform(input->begin(), input->end(), input->begin(), ::tolower);
		
		if (input->substr(0, 1).compare(".") == 0)
		{
			execute_meta_command(input);
		}
		else
		{
			execute_sql_statement(input, table);
		}
	}

	static MetaCommandResult execute_meta_command(string* command)
	{
		if (strcmp(command->c_str(), ".exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(command->c_str(), ".help") == 0)
		{
			printf("Meta command list:\n");
			printf(".help\n");
			printf(".exit\n");

			printf("\n");

			printf("Supported SQL syntax list:\n");
			printf("INSERT\n");
			printf("UPDATE\n");
			printf("DETETE\n");
			printf("SELECT\n");

			printf("\n");
		}
		else
		{
			printf("Unrecognized command '%s'.\n", command->c_str());
			return MetaCommandResult::META_UNRECOGNIZED_COMMAND;
		}

		return MetaCommandResult::META_COMMAND_SUCCESS;
	}

	static SQLCommandResult execute_sql_statement(string* statement_text, Table* table)
	{
		Statement statement;
		statement.text = *statement_text;
		PrepareResult result = prepare_sql_statement(&statement);

		if (result == PrepareResult::PREPARE_STATEMENT_SUCCESS)
		{
			switch (execute_statement(&statement, table)) 
			{
			case (ExecuteResult::EXECUTE_SUCCESS):
				printf("Executed.\n");
				break;
			case (ExecuteResult::EXECUTE_TABLE_FULL):
				printf("Error: Table full.\n");
				break;
			}
		}
		else if (result == PrepareResult::PREPARE_SYNTAX_ERROR)
		{
			printf("Syntax Error -- '%s'\n", Global::truncate_message(statement.text).c_str());
		}
		else if (result == PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT)
		{
			printf("Failed to prepare statement: unrecognized statement -- '%s'\n", Global::truncate_message(statement.text).c_str());
		}

		return SQLCommandResult::SQL_COMMAND_SUCCESS;
	}

	static ExecuteResult execute_statement(Statement* prepared_statement, Table* table)
	{
		switch (prepared_statement->type)
		{
		case (Types::STATEMENT_INSERT):
			return execute_insert(prepared_statement, table);
		case (Types::STATEMENT_SELECT):
			return execute_select(prepared_statement, table);
		case (Types::STATEMENT_DELETE):
			printf("Executed a DELETE.\n");
			break;
		case (Types::STATEMENT_UPDATE):
			printf("Executed a UPDATE.\n");
			break;
		}

		return ExecuteResult::EXECUTE_SUCCESS;
	}

	static ExecuteResult execute_insert(Statement* statement, Table* table)
	{
		if (table->number_of_rows >= table->TABLE_MAX_ROWS) 
		{
			return ExecuteResult::EXECUTE_TABLE_FULL;
		}

		Row *row_to_insert = &(statement->row);

		(statement->row).serialize_row(row_to_insert, (char*)row_slot(table, table->number_of_rows));
		table->number_of_rows += 1;

		return ExecuteResult::EXECUTE_SUCCESS;
	}

	static ExecuteResult execute_select(Statement* statement, Table* table) {
		Row row;
		for (uint32_t i = 0; i < table->number_of_rows; i++)
		{
			(statement->row).deserialize_row((char*)row_slot(table, i), &row);
			(statement->row).print_row(&row);
		}

		return ExecuteResult::EXECUTE_SUCCESS;
	}

	static PrepareResult prepare_sql_statement(Statement* statement)
	{
		if (strncmp(statement->text.c_str(), "select", 6) == 0)
		{
		statement->type = Types::STATEMENT_SELECT;
		return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement->text.c_str(), "insert", 6) == 0)
		{
			statement->type = Types::STATEMENT_INSERT;

			int args_assigned = sscanf
				(
					statement->text.c_str(), 
					"insert %d %s %s", 
					&(statement->row.id),
					statement->row.username, 
					statement->row.email
				);

			if (args_assigned < 3) 
			{
				return PrepareResult::PREPARE_SYNTAX_ERROR;
			}

			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement->text.c_str(), "update", 6) == 0)
		{
			statement->type = Types::STATEMENT_UPDATE;
			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement->text.c_str(), "delete", 6) == 0)
		{
			statement->type = Types::STATEMENT_DELETE;
			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else
		{
			return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
		}
	}
};
