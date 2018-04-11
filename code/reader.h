#pragma once
#include <fstream>
#include <sstream>

using namespace std;

class Reader {
public:
	Reader(const string filename);
	bool isEof() { return this->data_file.eof(); }

	// Returns the number of input values read from the file:
	int get_inputs(vector<double> &inputs);
	int get_outputs(vector<double> &outputs);

private:
	ifstream data_file;
};

Reader::Reader(const string filename) {
	this->data_file.open(filename);
}

int Reader::get_inputs(vector<double> &inputs) {
    inputs.clear();

    string line;
    getline(this->data_file, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label.compare("input:") == 0) {
        double input;
        while (ss >> input) inputs.push_back(input);
    }

    return inputs.size();
}

int Reader::get_outputs(vector<double> &outputs) {
    outputs.clear();

    string line;
    getline(this->data_file, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label.compare("output:") == 0) {
        double output;
        while (ss >> output) outputs.push_back(output);
    }

    return outputs.size();
}
