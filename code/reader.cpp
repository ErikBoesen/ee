#include <vector>
#include <fstream>
#include <map>
#include "reader.hpp"
// TODO: Experiment with larger values for N
#define N 1000

// Constants defining the starting and ending of the ASCII range we want to pay attention to
#define TRACK_START 32
#define TRACK_END 126

using namespace std;

Reader::Reader(const string language) {
	this->data_file.open("data/languages/" + language);
}

int Reader::get_ngram(vector<double> &ngram) {
    ngram.clear();
	for (int i = 0; i < N; i++)
        ngram.push_back(this->data_file.get());
    return ngram.size();
}

map<char, double> Reader::get_rates() {
    map<char, int> counts;
    for (char c = TRACK_START; c <= TRACK_END; c++) {
        counts[c] = 0;
    }
    int i;
    for (char c; i < N; this->data_file.get(c)) {
        if (c > 32 || c < 127) {
            i++;
            counts[c]++;
        }
    }
    map<char, double> rates;
    for (char c = TRACK_START; c <= TRACK_END; c++) {
        rates[c] = counts[c] / N;
    }
    return rates;
}
