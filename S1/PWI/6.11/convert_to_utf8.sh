#!/bin/bash

for file in *txt; do
    if file -i $file | grep -q 'utf-8'; then
        echo "$file is in UTF-8"
    else
        iconv -f ISO-8859-2 $file -t UTF-8 -o ${file%.txt}.utf8.converted.txt
        mv ${file%.txt}.utf8.converted.txt $file
    fi
done