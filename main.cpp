#include <iostream>
#include "parser.h"
#include "parser.cpp"
#include "lexer.cpp"
#include "lexer.h"
#include "VM.h"
#include "VM.cpp"
using namespace std;

int main(int argc, char* argv[])
{
	//asking for file name as command line arguments
	if (argc == 2)
	{

		//uncomment this line of parse
		//parser _parser(argv[1]);
		
		
		
		// lexer _lexer(argv[1]);
		// token t;
		// t = _lexer.getNextToken();

		// while (t.tokenType != TokenType::END_OF_FILE)
		// {
		// 	t.Print();
		// 	t = _lexer.getNextToken();
		// }


		VM vm;
		vm.start();

		// OpCode op;
		// op.load_code_in_stream("Tac.txt");
	}
	else if (argc > 2)
	{ //argument limit exceeds
		cout << "Too many arguments" << endl;
	}
	else //if file name is'nt given
	{
		cout << "Please provide a file name" << endl;
	}
	return 0;
}
