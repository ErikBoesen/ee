#!/usr/bin/env bash

# List languages for iteration
langs=(zh es en ar hi bn pt ru)

# Filename endings for easier looping
files=(
    articles1.xml-p1p231819.bz2
    articles1.xml-p5p229076.bz2
    articles1.xml-p10p30302.bz2
    articles.xml.bz2
    articles.xml.bz2
    articles.xml.bz2
    articles1.xml-p220p158755.bz2
    articles1.xml-p4p311181.bz2
)

# Date of dump from which to download
date=20180420

# Iterate through languages
for ((i=0; i<${#langs[@]}; ++i)); do
    # Only download database if files don't already exist
    if [[ ! -e ${langs[i]}.xml ]] && [[ ! -e ${langs[i]}.xml.bz2 ]]; then
        echo "Downloading ${langs[i]}..."
        # Download and decompress database file
        curl -o ${langs[i]}.xml.bz2 https://dumps.wikimedia.org/${langs[i]}wiki/$date/${langs[i]}wiki-$date-pages-${files[i]}
        echo "Decompressing ${langs[i]}..."
        bzip2 -d ${langs[i]}.xml.bz2
    else
        echo ${langs[i]} already downloaded.
    fi
done
