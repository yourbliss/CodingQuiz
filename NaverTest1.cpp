
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

bool debugging = false;


int main() {

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

	map<string, unsigned int> maps;
	// input until EOF
	while (!src_file.eof())
	{
		string input;
		getline(src_file, input);

		if (!input.empty())
			maps[input] = (maps.find(input) == maps.end()) ? 1 : maps[input] + 1;
	}

	src_file.close();


	// output
	// condition1. find person who get the highest score
	// condition2. if same score, show as dictionary order

	vector<string> names;
	unsigned int max = 0;

	map<string, unsigned int>::iterator mb = maps.begin();
	map<string, unsigned int>::iterator me = maps.end();
	for (; mb != me; ++mb)
	{
		if (mb->second > max)
		{
			names.clear();
			max = mb->second;
			names.push_back(mb->first);
		}
		else if (mb->second == max)
			names.push_back(mb->first);
	}

	vector<string>::iterator vb = names.begin();
	vector<string>::iterator ve = names.end();

//	cout << "=========== RESULT VOTE =============" << endl;
//	cout << "Total " << names.size() << " same score with " << max << endl;
	for (; vb != ve; ++vb)
	{
		cout << vb->c_str() << endl;
	}

	return 0;
}
