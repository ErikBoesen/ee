#!/bin/bash
N=1000
line_total=0
char_total=0
for language in $(ls languages); do
    line_count=$(wc -l languages/$language | awk '{print $1}')
    char_count=$(wc -c languages/$language | awk '{print $1}')
    ((line_total+=line_count))
    ((char_total+=char_count))
    echo "$language: $line_count lines, $char_count characters, $((char_count/N)) $N-grams"
done
echo "Total: $line_total lines, $char_total characters, $((char_total/N)) $N-grams"
