class Statement
{
public:
	Statement() 
	{
		type = Types::UNKNOWN;
	};
	~Statement() {};

	Types::StatementType type;
	Row row;
	string text;
};
