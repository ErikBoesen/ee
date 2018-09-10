from keras.models import Sequential
from keras.layers import Dense
import numpy
# fix random seed for reproducibility
numpy.random.seed(7)

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
TRAINING_EPOCHS = 1000

class Reader:
    pass

languages = ["Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "SQL", "Ruby"]


readers = [Reader(language) for language in languages]

vector<int> topology;
int input_size = TRACK_END - TRACK_START + 1;
// Input layer
topology.push_back(input_size);
// Hidden layers
while (input_size > NUM_LANGS) {
cout << "Making a hidden layer of size " << input_size << endl;
input_size *= 0.75;
cout << "input_size is now " << input_size << endl;
topology.push_back(input_size);
}
// Output Layer
topology.push_back(NUM_LANGS);
Net network(topology);

vector<double> rates, targets, results;

// Trim decimals
cout << fixed << setprecision(0);

for (int epoch = 0; epoch < TRAINING_EPOCHS; ++epoch) {
        for (int lang_ind = 0; lang_ind < NUM_LANGS; ++lang_ind) {
                // Get new input data and feed it forward
                readers[lang_ind]->get_rates(rates);

                network.feed_forward(rates);

                // Collect the network's results
                network.get_results(results);

                // Generate correct outputs
                //reader.get_outputs(targets);
                targets.clear();
                for (int field = 0; field < NUM_LANGS; ++field) targets.push_back(0);
                targets[lang_ind] = 1;
                assert(targets.size() == topology.back());

                // Backpropogate!
                network.backpropogate(targets);

                cout << "\033[36mE" << epoch << " (" << languages[lang_ind] << ',' << lang_ind << ") / \033[33m";
                //print_ngram(rates);
                cout << "\033[0m > \033[32m";
                cout << setprecision(PRECISION);
                print_vector(results);
                cout << " \033[31merr";
                print_error(results, targets);
                cout << endl;
        }
}

// Isn't it gorgeous?
for (Reader *r : readers) delete r;








model = Sequential()
model.add(Dense(12, input_dim=, activation='relu'))
model.add(Dense(8, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])
