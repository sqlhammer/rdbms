
enum class MetaCommandResult
{
	UNKOWN,
	META_COMMAND_SUCCESS,
	META_UNRECOGNIZED_COMMAND
};

enum class SQLCommandResult
{
	UNKOWN,
	SQL_COMMAND_SUCCESS,
	SQL_UNRECOGNIZED_COMMAND
};

enum class ExecuteResult
{
	UNKOWN,
	EXECUTE_SUCCESS,
	EXECUTE_TABLE_FULL
};

enum class PrepareResult
{
	UNKOWN,
	PREPARE_STATEMENT_SUCCESS,
	PREPARE_SYNTAX_ERROR,
	PREPARE_UNRECOGNIZED_STATEMENT
};
