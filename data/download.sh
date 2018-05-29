#!/bin/bash
url=https://github.com/acmeism/RosettaCodeData
repo=/tmp/RosettaCodeData
languages=("Java" "C" "C++" "Python" "C-sharp" "Visual-Basic-.NET" "PHP" "JavaScript" "SQL" "Ruby")

if [ ! -e $repo ]; then
    git clone $url $repo
fi

mkdir language
for language in "${languages[@]}"; do
    echo $language
    mkdir language/$language
    cp $repo/Task/*/$language/* languages/$language/
done
