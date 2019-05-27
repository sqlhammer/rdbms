static class Types
{
public:
	Types() {};
	~Types() {};

	enum StatementType
	{
		STATEMENT_INSERT,
		STATEMENT_SELECT,
		STATEMENT_DELETE,
		STATEMENT_UPDATE
	};
};

