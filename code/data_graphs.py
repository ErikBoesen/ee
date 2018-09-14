import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
languages = ["Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "Ruby", "R"]

text = [open('data/languages/' + language).read() for language in languages]
for lang_ind in range(NUM_LANGS):
    rates = [0.0] * (TRACK_END - TRACK_START)
    # Go through each character in file, adding to the rates appropriately
    for c in text[lang_ind]:
        if TRACK_START <= ord(c) < TRACK_END:
            rates[ord(c) - TRACK_START] += 1
    # Turn rates into rates rather than counts
    rates = [rate / len(text[lang_ind]) for rate in rates]
    print(rates)

