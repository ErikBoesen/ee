import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
COLS = 2
ROWS = NUM_LANGS // COLS
languages = ['Java', 'C', 'C++', 'Python', 'C-sharp', 'Visual-Basic-.NET',
             'PHP', 'JavaScript', 'Ruby', 'R']
colors = ['#d34410', '#ff6e00', '#0d94a3', '#084c61', '#050f42',
          '#853037', '#ff3d4e', '#d25f6c', '#143d1d', '#387a4a']

text = [open('data/languages/' + language).read() for language in languages]
x = list(range(TRACK_END))
figure(figsize=(18, 3))
for lang_ind in range(NUM_LANGS):
    rates = [0.0] * (TRACK_END)
    # Go through each character in file, adding to the rates appropriately
    for c in text[lang_ind]:
        if TRACK_START <= ord(c) < TRACK_END:
            rates[ord(c)] += 1
    # Turn rates into rates rather than counts
    rates = [rate / len(text[lang_ind]) for rate in rates]
    print(rates)
    plt.subplot(ROWS, COLS, lang_ind + 1)
    plt.subplots_adjust(top=3, bottom=0.5)
    plt.grid(True)
    plt.title(languages[lang_ind])
    plt.xlim(TRACK_START, TRACK_END + 1)
    plt.ylim(0, 0.07)
    plt.bar(x, rates, color=colors[lang_ind], align='edge')
    plt.bar(x, rates, color=colors[lang_ind], align='center', width=0.3)
    if lang_ind + 1 > COLS:
        plt.xlabel('Character')
    #else:
        #plt.xticks([])
    if lang_ind % COLS == 0:
        plt.ylabel('Frequency')
    #else:
        #plt.yticks([])

plt.savefig('../images/frequencies.png', bbox_inches='tight')
