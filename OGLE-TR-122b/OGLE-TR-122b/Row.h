class Row
{
public:
	Row() {};
	~Row() {};

	static const int COLUMN_USERNAME_SIZE = 32;
	static const int COLUMN_EMAIL_SIZE = 255;

	int id;
	char username[COLUMN_USERNAME_SIZE];
	char email[COLUMN_EMAIL_SIZE];

	static const int ROW_SIZE = sizeof(id) + COLUMN_EMAIL_SIZE + COLUMN_USERNAME_SIZE;

	static const int USERNAME_OFFSET = sizeof(id);
	static const int EMAIL_OFFSET = sizeof(id) + COLUMN_USERNAME_SIZE;

	void serialize_row(Row* source, char* destination) 
	{
		memcpy(destination, &(source->id), sizeof(id));
		memcpy(destination + USERNAME_OFFSET, &(source->username), COLUMN_USERNAME_SIZE);
		memcpy(destination + EMAIL_OFFSET, &(source->email), COLUMN_EMAIL_SIZE);
	}
	
	void deserialize_row(char* source, Row* destination) 
	{
		memcpy(&(destination->id), source, sizeof(id));
		memcpy(&(destination->username), source + USERNAME_OFFSET, COLUMN_USERNAME_SIZE);
		memcpy(&(destination->email), source + EMAIL_OFFSET, COLUMN_EMAIL_SIZE);
	}

	void print_row(Row* row) 
	{
		printf("(%d, %s, %s)\n", row->id, row->username, row->email);
	}
};
