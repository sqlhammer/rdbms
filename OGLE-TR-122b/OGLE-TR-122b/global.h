
using namespace std;

static class Global
{
public:
	Global() {};
	~Global() {};

	static const int MAX_MESSAGE_LENGTH = 100;

	//BEGIN table sizing
	static const int TABLE_MAX_PAGES = 100;
	static const int PAGE_SIZE = 8192; //8 KB
	//END table sizing

	static string truncate_message(string &input)
	{
		return input.substr(0, MAX_MESSAGE_LENGTH);
	}

	template <typename Enumeration>
	auto as_integer(Enumeration const value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}
};
