
using namespace std;

static class UserInterface
{
public:
	UserInterface() {};
	~UserInterface() {};
	
	static void print_header(string version)
	{
		cout << "Welcome to project OGLE-TR-112b (OGLE for short)." << endl;
		cout << "Developer: Derik Hammer (www.sqlhammer.com)" << endl;
		cout << "Project start date: 05/27/2019" << endl;
		cout << "Version: " << version.c_str() << endl << endl;
		cout << "Execute \".help\" for command information." << endl << endl << endl;
	}

	static void REPL()
	{
		//read execute print loop
		//used for all user interactions and command execution

		while (true)
		{
			string input = "";
			print_prompt();
			read_input(input);
			Parser::parse_execute(input);
		}
	}

	static void print_prompt()
	{
		cout << "ogle > ";
	}

	static void read_input(string &input)
	{
		try
		{
			getline(cin, input);
		}
		catch (exception e)
		{
			cout << "Error reading input." << endl;
		}
	}
};


