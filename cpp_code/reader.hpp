#pragma once
#include <fstream>
#include <map>

// TODO: Experiment with larger values for N
#define N 1000
// The starting and ending of the ASCII range we want to pay attention to
#define TRACK_START 32
#define TRACK_END 126

using namespace std;

class Reader {
public:
	Reader(const string language);

    // Deprecated
	int get_ngram(vector<double> &ngram);
    int get_rates(vector<double> &rates);


private:
	ifstream data_file;
};
