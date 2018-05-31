#!/bin/bash
N=8
file_total=0
line_total=0
char_total=0
for language in $(ls languages); do
    file_count=$(ls languages/$language | wc -l | awk '{print $1}')
    line_count=$(wc -l languages/$language/* | tail -1 | awk '{print $1}')
    char_count=$(wc -c languages/$language/* | tail -1 | awk '{print $1}')
    ((file_total+=file_count))
    ((line_total+=line_count))
    ((char_total+=char_count))
    echo "$language: $file_count files $line_count lines $char_count characters $((char_count/N)) $N-grams"
done
echo "Total: $file_total files $line_total lines $char_total characters $((char_total/N)) $N-grams"
