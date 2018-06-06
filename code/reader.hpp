#pragma once
#include <fstream>
#include <sstream>

using namespace std;

class Reader {
public:
	Reader(const string language, int language_index, int num_languages);
	bool isEof() { return this->data_file.eof(); }

	// Returns the number of input values read from the file:
	int get_inputs(vector<double> &inputs);
	int get_outputs(vector<double> &outputs);

private:
	ifstream data_file;
};
