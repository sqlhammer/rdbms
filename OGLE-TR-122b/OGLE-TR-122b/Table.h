class Table
{
public:
	Table() 
	{ 
		number_of_rows = 0;
	};
	~Table() {};

	static const int ROW_SIZE = Row::ROW_SIZE;
	static const int ROWS_PER_PAGE = Global::PAGE_SIZE / ROW_SIZE;
	static const int TABLE_MAX_ROWS = ROWS_PER_PAGE * Global::TABLE_MAX_PAGES;

	int number_of_rows;
	void* pages[Global::TABLE_MAX_PAGES] = { NULL };
};
