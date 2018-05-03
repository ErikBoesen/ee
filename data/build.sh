#!/usr/bin/env bash

langs=(zh es en ar hi bn pt ru)
for l in ${langs[@]}; do
    echo $l...
done

curl -o zh.xml.bz2 https://dumps.wikimedia.org/zhwiki/20180420/zhwiki-20180420-pages-articles1.xml-p1p231819.bz2
curl -o es.xml.bz2 https://dumps.wikimedia.org/eswiki/20180420/eswiki-20180420-pages-articles1.xml-p5p229076.bz2
curl -o en.xml.bz2 https://dumps.wikimedia.org/enwiki/20180420/enwiki-20180420-pages-articles1.xml-p10p30302.bz2
curl -o ar.xml.bz2 https://dumps.wikimedia.org/arwiki/20180420/arwiki-20180420-pages-articles.xml.bz2
curl -o hi.xml.bz2 https://dumps.wikimedia.org/hiwiki/20180420/hiwiki-20180420-pages-articles.xml.bz2
curl -o bn.xml.bz2 https://dumps.wikimedia.org/bnwiki/20180420/bnwiki-20180420-pages-articles.xml.bz2
curl -o pt.xml.bz2 https://dumps.wikimedia.org/ptwiki/20180420/ptwiki-20180420-pages-articles1.xml-p220p158755.bz2
curl -o ru.xml.bz2 https://dumps.wikimedia.org/ruwiki/20180420/ruwiki-20180420-pages-articles1.xml-p4p311181.bz2
