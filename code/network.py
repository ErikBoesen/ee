from keras.models import Sequential
from keras.layers import Dense
import numpy as np
from sklearn.model_selection import train_test_split
import json

seed = 7
np.random.seed(seed)

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
TRAINING_EPOCHS = 100

languages = ['Java', 'C', 'C++', 'Python', 'C-sharp', 'Visual-Basic-.NET',
             'PHP', 'JavaScript', 'Ruby', 'R']

input_dim = TRACK_END - TRACK_START;

dataset = np.loadtxt('data.csv', delimiter=',')
# Randomize order of training samples
np.random.shuffle(dataset)

X = dataset[:,0:input_dim]
Y = dataset[:,input_dim:input_dim+NUM_LANGS]
print(X)
print(Y)
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=seed)

model = Sequential()
# Significantly higher success when using ReLU as activation function than sigmoid.
model.add(Dense(48, input_dim=input_dim, activation='relu'))
model.add(Dense(24, activation='relu'))
model.add(Dense(NUM_LANGS, activation='sigmoid'))

model.compile(loss='categorical_crossentropy', optimizer='nadam', metrics=['accuracy'])

fit = model.fit(X_train, Y_train, epochs=int(TRAINING_EPOCHS * 0.8), batch_size=NUM_LANGS)
scores = model.evaluate(X_test, Y_test)
print(scores)
print('Accuracy: %.2f%%' % (scores[1] * 100))

with open('history.json', 'w') as f:
    json.dump(fit.history, f)
