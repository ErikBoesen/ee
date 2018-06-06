#include <vector>
#include <fstream>
#include "reader.hpp"
#define N 8

using namespace std;

Reader::Reader(const string language, int language_index, int num_languages) {
	this->language = language;
	this->language_index = lanuage_index;
	this->num_languages = num_languages;
	this->data_file.open("data/languages/" + language);
}

int Reader::get_ngram(vector<double> &ngram) {
    inputs.clear();
	for (int i = 0; i < N; i++)
		inputs.push_back((double)(this->data_file.get()));
    return inputs.size();
}

int Reader::get_outputs(vector<double> &outputs) {
    outputs.clear();
	for (int i = 0; i < this->num_languages; i++) outputs.push_back(0);
	outputs[self.language_index] = 1;

    return outputs.size();
}
