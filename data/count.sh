#!/bin/bash
file_total=0
line_total=0
for language in $(ls languages); do
    file_count=$(ls languages/$language | wc -l | awk '{print $1}')
    line_count=$(wc -l languages/$language/* | tail -1 | awk '{print $1}')
    echo "$language: $file_count files $line_count lines"
    file_total=$((file_total+file_count))
    line_total=$((line_total+line_count))
done
echo "Total: $file_total files $line_total lines"
