#!/bin/sh

echo "NOTE: Particular comments may generate false positives."
echo "NOTE: Declaring and dereferencing pointers will generate false positives"
echo

for pattern in + - '\*' / %
do
	echo [CHECKING] ${pattern} in alu.c
	if [ $pattern == '\*' ]
	then
		grep "${pattern}" alu.c | grep -v "^\s*\*" | grep -v "/\*.*${pattern}" | grep -v "//.*${pattern}" | grep -v "/\*"
	elif [ $pattern == / ]
	then
		grep "${pattern}" alu.c | grep -v "^\s*\*" | grep -v "/\*.*${pattern}" | grep -v "//.*${pattern}" | grep -v "/\*" | grep -v "//"
	else
		grep "${pattern}" alu.c | grep -v "^\s*\*" | grep -v "/\*.*${pattern}" | grep -v "//.*${pattern}"
	fi
	grep -e ".*${pattern}.*/\*" -e ".*${pattern}.*//" -e "\*/.*${pattern}" alu.c
done

