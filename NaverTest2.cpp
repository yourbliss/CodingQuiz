#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Calculator {
	public:
		Calculator(string input):data(input), result(0), error(false){}
		void calculate();
		void show();


	private:
		Calculator():result(0), error(false){}

		enum TokenType { Op, Val };

		class Token {
			public:
				Token():type(Op), value(0){}
				Token(int t, unsigned long v):type(t), value(v){}
				int type;
				unsigned long value;
		};

		string data;
		stack<Token> tokens;
		unsigned long result;
		bool error;
};

void Calculator::show()
{
	if (error)
	{
		cout << 0 <<endl;
		return;
	}
	while (!tokens.empty())
	{
		result += tokens.top().value;
		tokens.pop();
	}
	cout << result % 100000000 <<endl;
}


void Calculator::calculate()
{
	unsigned long sum = 0;
	for (size_t i = 0; i < data.size(); ++i)
	{
		unsigned long value = 0;
		switch (data[i])
		{
		case '(' : tokens.push(Token(Op, 1)); break;
		case '{' : tokens.push(Token(Op, 2)); break;
		case '[' : tokens.push(Token(Op, 3)); break;
		case ')' : value = 1; break;
		case '}' : value = 2; break;
		case ']' : value = 3; break;
		default:
			error = true;
			return;
		}

		// termination
		if (value == 0) continue;
		if (tokens.empty())
		{
			error = true;
			return;
		}
		// check top
		Token top = tokens.top();
		tokens.pop();

		if (top.type == Op)
		{
			if (top.value != value)
			{
				error = true;
				return;
			}
			tokens.push(Token(Val, value));
		}
		else
		{
			sum = top.value;
			while(!tokens.empty())
			{
				top = tokens.top();
				tokens.pop();

				if (top.type == Op)
				{
					if (top.value != value)
					{
						error = true;
						return;
					}
					break;
				}
				sum += top.value;
			}

			tokens.push(Token(Val, (sum * value)));
		}
	}
}

int main()
{
	string input_filepath;

	cout << "enter input path(full path with filename)." << endl;
	getline(cin, input_filepath);

	// input from file
	ifstream src_file(input_filepath.c_str());

	// handle failure
	if (src_file.fail())
	{
		cout << "Failed to open file:" << input_filepath << endl;
		return 1;
	}
	else
		cout << input_filepath << " opened" << endl;
	// first line is total number of tests

	string s_numtest;
	getline(src_file, s_numtest);

	int num_tests = atoi(s_numtest.c_str());
	int num_getlines = 0;
	while(!src_file.eof())
	{
		++num_getlines;
		if (num_getlines > num_tests) return 0;
		string input;
		getline(src_file, input);
		Calculator calc(input);
		calc.calculate();
		calc.show();

	}

    return 0;
}



