from keras.models import Sequential
from keras.layers import Dense
import numpy as np
# TODO: numpy can be used to load CSVs, I believe.
import pandas as pd

# fix random seed for reproducibility
np.random.seed(7)

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
TRAINING_EPOCHS = 25  # Again, this is the largest we can do with SQL.

class Reader:
    pass

languages = ["Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "SQL", "Ruby"]

input_dim = TRACK_END - TRACK_START;

dataset = np.loadtxt('data.csv', delimiter=',')

X = dataset[:,0:input_dim]
Y = dataset[:,input_dim:input_dim+NUM_LANGS]
print(X)
print(Y)


model = Sequential()
model.add(Dense(48, input_dim=input_dim, activation='relu'))
model.add(Dense(24, activation='relu'))
model.add(Dense(NUM_LANGS, activation='sigmoid'))

model.compile(loss='categorical_crossentropy', optimizer='nadam', metrics=['accuracy'])

model.fit(X, Y, epochs=TRAINING_EPOCHS, batch_size=NUM_LANGS)

scores = model.evaluate(X, Y)
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))
