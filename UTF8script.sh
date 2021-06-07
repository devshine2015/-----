#!/bin/sh
# convert GB18030 code page to utf-8

for file in *.h
do
    iconv -f GB18030 -t utf-8 $file > $file.k
    rm $file
    mv $file.k $file
done

for file in *.cpp
do
    iconv -f GB18030 -t utf-8 $file > $file.k
    rm $file
    mv $file.k $file
done
# find . -name '*.cpp' -exec iconv -f GB18030 -t utf-8 {} > {} \;
# find . -name '*.h' -exec iconv -f GB18030 -t utf-8 {} > {} \;
