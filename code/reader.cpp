#include <vector>
#include <fstream>
#include "reader.hpp"
#define N 8

using namespace std;

Reader::Reader(const string language, int language_index, int num_languages) {
	this->language = language;
	this->language_index = language_index;
	this->num_languages = num_languages;
	this->data_file.open("data/languages/" + language);
}

int Reader::get_ngram(vector<double> &ngram) {
    ngram.clear();
	for (int i = 0; i < N; i++)
		ngram.push_back((double)(this->data_file.get()));
    return ngram.size();
}
