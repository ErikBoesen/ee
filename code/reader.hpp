#pragma once
#include <fstream>
#include <map>

using namespace std;

class Reader {
public:
	Reader(const string language);

    // Deprecated
	int get_ngram(vector<double> &ngram);
    vector<double> get_rates();


private:
	ifstream data_file;
};
