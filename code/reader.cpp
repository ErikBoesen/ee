#include <vector>
#include <fstream>
#include "reader.hpp"
#define N 8

using namespace std;

Reader::Reader(const string language) {
	this->language = language;
	this->data_file.open("data/languages/" + language);
}

int Reader::get_ngram(vector<double> &ngram) {
    ngram.clear();
	for (int i = 0; i < N; i++)
		ngram.push_back(this->data_file.get());
    return ngram.size();
}
