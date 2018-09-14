import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
EPOCHS = 100  # More epochs would be ideal. Visual Basic .NET does not have many solutions on RosettaCode.
N = 1000
languages = ["Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "Ruby", "R"]

text = [open('data/languages/' + language).read() for language in languages]
for lang_ind in range(NUM_LANGS):
    rates = [0.0] * (TRACK_END - TRACK_START)
    # Go through each character in file, adding to the rates appropriately
    for c in block:
        if TRACK_START <= ord(c) < TRACK_END:
            rates[ord(c) - TRACK_START] += 1
    # Turn rates into rates rather than counts
    rates = [rate / N for rate in rates]
    print(rates)

