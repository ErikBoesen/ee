import csv

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
EPOCHS = 100
N = 1000
languages = ['Java', 'C', 'C++', 'Python', 'C-sharp', 'Visual-Basic-.NET',
             'PHP', 'JavaScript', 'Ruby', 'R']

text = [open('data/languages/' + language).read() for language in languages]
data = []
for epoch in range(EPOCHS):
    for lang_ind in range(NUM_LANGS):
        rates = [0.0] * (TRACK_END - TRACK_START)
        block = text[lang_ind][:N]
        text[lang_ind] = text[lang_ind][N:]
        # Go through each character in block, adding to the rates appropriately
        for c in block:
            if TRACK_START <= ord(c) < TRACK_END:
                rates[ord(c) - TRACK_START] += 1
        print(block)
        if not block:
            import sys
            print('Not enough data for ' + languages[lang_ind])
            sys.exit(1)
        # Turn rates into rates rather than counts
        rates = [rate / N for rate in rates]
        print(rates)
        lang_binaries = [0] * NUM_LANGS
        lang_binaries[lang_ind] = 1
        data.append(rates + lang_binaries)


with open('data.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    for row in data:
        writer.writerow(row)
