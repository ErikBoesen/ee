#pragma once
#include <fstream>

using namespace std;

class Reader {
public:
	Reader(const string language);

	int get_ngram(vector<double> &ngram);

private:
	ifstream data_file;
};
