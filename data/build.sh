#!/usr/bin/env bash

langs=(zh es en ar hi bn pt ru)
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
date=20180420

for ((i=0; i<${#langs[@]}; ++i)); do
    if [[ ! -e ${langs[i]}.xml ]] && [[ ! -e ${langs[i]}.xml.bz2 ]]; then
        echo ${langs[i]}...
        curl -o ${langs[i]}.xml.bz2 https://dumps.wikimedia.org/${langs[i]}wiki/$date/${langs[i]}wiki-$date-pages-${files[i]}
        bzip2 -d ${langs[i]}.xml.bz2
    fi
done
