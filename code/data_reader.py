

TRACK_START = 32
TRACK_END = 126

NUM_LANGS = 10
EPOCHS = 1000
N = 1000
languages = ["Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "SQL", "Ruby"]
text = [open('data/languages/' + language).read() for language in languages]
for epoch in range(EPOCHS):
    for lang_ind in range(NUM_LANGS):
        rates = [0.0] * (TRACK_END - TRACK_START)
        block = text[lang_ind][:N]
        text[lang_ind] = text[lang_ind][N:]
        for c in block:
            if TRACK_START <= ord(c) < TRACK_END:
                rates[ord(c) - TRACK_START] += 1
        print(block)
        print(rates)


for f in files:
    f.close()
