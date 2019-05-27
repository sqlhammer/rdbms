
using namespace std;

static class Helper
{
public:
	Helper() {};
	~Helper() {};

	static const int max_message_length = 100;

	static string truncate_message(string &input)
	{
		return input.substr(0, max_message_length);
	}

	template <typename Enumeration>
	auto as_integer(Enumeration const value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}
};
