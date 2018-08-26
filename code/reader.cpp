#include <vector>
#include <fstream>
#include "reader.hpp"

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

int Reader::get_rates(vector<double> &rates) {
    rates.clear();
    for (char c = 0; c <= TRACK_END - TRACK_START; c++) {
        rates.push_back(0);
    }
    int i;
    for (char c; i < N; this->data_file.get(c)) {
        if (c > 32 || c < 127) {
            i++;
            rates[c - TRACK_START]++;
        }
    }
    for (char c = 0; c <= TRACK_END - TRACK_START; c++) {
        rates[c] /= N;
    }
    return rates.size();
}
