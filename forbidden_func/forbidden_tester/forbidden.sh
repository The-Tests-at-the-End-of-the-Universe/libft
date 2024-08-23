#!/bin/bash

RED="\x1B[31m"
GRN="\x1B[1;32m"
YEL="\x1B[33m"
BLU="\x1B[34m"
MAG="\x1B[35m"
BMAG="\x1B[1;35m"
CYN="\x1B[36m"
BCYN="\x1B[1;36m"
WHT="\x1B[37m"
RESET="\x1B[0m"
LINEP="\033[40G"

exe=$1
config=$2
extra_cmd=$3

fail=false

if [ -f output ];
then
rm -rf output
fi

if [ -f $exe ];
then
:
else 
echo -e "file does not exist"
exit 1
fi

if [ -f $config ];
then
:
else 
echo -e "config does not exist"
exit 1
fi

echo " nm -unj $exe | grep -v __ $extra_cmd > output" | bash


if [ -s output ];
then 
:
else 
echo "✅"
fi

loop=false
while read -r output_line
do
	loop=true
	fail=true
	while read -r line
	do
	if [ "$output_line" == "$line" ];
	then
	fail=false
	fi
	done < "$config"
	if [ $fail == true ];
	then 
	echo
	echo -ne "$RED FAIL: $output_line is illegal $RESET"
	fi
done < "output"

if [[ $fail == false && $loop == true ]];
then
echo "✅"
fi

rm -rf output
if [ $fail == true ];
then 
echo
exit 1
else
exit 0
fi
