
using namespace std;

static class Parser
{
public:
	Parser() {};
	~Parser() {};

	static void parse_execute(string &input)
	{
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		
		if (input.substr(0, 1).compare(".") == 0)
		{
			execute_meta_command(input);
		}
		else
		{
			execute_sql_statement(input);
		}
	}

	static MetaCommandResult execute_meta_command(string &command)
	{
		if (strcmp(command.c_str(), ".exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(command.c_str(), ".help") == 0)
		{
			printf("Meta command list:\n");
			printf(".help\n");
			printf(".exit\n");

			printf("\n");
		}
		else
		{
			printf("Unrecognized command '%s'.\n", command.c_str());
			return MetaCommandResult::META_UNRECOGNIZED_COMMAND;
		}

		return MetaCommandResult::META_COMMAND_SUCCESS;
	}

	static SQLCommandResult execute_sql_statement(string &statement_text)
	{
		Statement statement;
		statement.text = statement_text;
		PrepareResult result = prepare_sql_statement(statement);

		if (result == PrepareResult::PREPARE_STATEMENT_SUCCESS)
		{
			execute_statement(statement);
		}
		else if (result == PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT)
		{
			printf("Failed to prepare statement: unrecognized statement -- '%s'\n", Helper::truncate_message(statement.text).c_str());
		}

		return SQLCommandResult::SQL_COMMAND_SUCCESS;
	}

	static SQLCommandResult execute_statement(Statement &prepared_statement)
	{
		switch (prepared_statement.type)
		{
		case (Types::STATEMENT_INSERT):
			printf("Executed a INSERT.\n");
			break;
		case (Types::STATEMENT_SELECT):
			printf("Executed a SELECT.\n");
			break;
		case (Types::STATEMENT_DELETE):
			printf("Executed a DELETE.\n");
			break;
		case (Types::STATEMENT_UPDATE):
			printf("Executed a UPDATE.\n");
			break;
		}

		return SQLCommandResult::SQL_COMMAND_SUCCESS;
	}

	static PrepareResult prepare_sql_statement(Statement &statement)
	{
		if (strncmp(statement.text.c_str(), "select", 6) == 0)
		{
		statement.type = Types::STATEMENT_SELECT;
		return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement.text.c_str(), "insert", 6) == 0)
		{
			statement.type = Types::STATEMENT_INSERT;
			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement.text.c_str(), "update", 6) == 0)
		{
			statement.type = Types::STATEMENT_UPDATE;
			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else if (strncmp(statement.text.c_str(), "delete", 6) == 0)
		{
			statement.type = Types::STATEMENT_DELETE;
			return PrepareResult::PREPARE_STATEMENT_SUCCESS;
		}
		else
		{
			return PrepareResult::PREPARE_UNRECOGNIZED_STATEMENT;
		}
	}
};
