class Statement
{
public:
	Statement() 
	{
		type = Types::UNKNOWN;
	};
	~Statement() {};

	Types::StatementType type;
	string text;
};
