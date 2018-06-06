#pragma once
#include <fstream>

using namespace std;

class Reader {
public:
	Reader(const string language, int language_index);

	int get_ngram(vector<double> &ngram);
	int get_language_index() { return this->language_index; }

private:
	ifstream data_file;
	string language;
	int language_index;
};
