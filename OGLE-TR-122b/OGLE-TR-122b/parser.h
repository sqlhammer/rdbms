
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

	static Results::MetaCommandResult execute_meta_command(string &input)
	{
		if (strcmp(input.c_str(), ".exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(input.c_str(), ".help") == 0)
		{
			printf("Meta command list:\n");
			printf(".help\n");
			printf(".exit\n");

			printf("\n");
		}
		else
		{
			printf("Unrecognized command '%s'.\n", input.c_str());
			return Results::META_UNRECOGNIZED_COMMAND;
		}

		return Results::META_COMMAND_SUCCESS;
	}

	static Results::SQLCommandResult execute_sql_statement(string &input)
	{
		printf("Stubbed execution of a SQL statement.\n");

		return Results::SQL_COMMAND_SUCCESS;
	}

};
