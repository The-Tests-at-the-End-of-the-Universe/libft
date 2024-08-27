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

if [ ! -f $(find ../../ -type f -name "*.o") ];
then 
make -C "../../" re &> /dev/null
else
:
fi

echo -e "$YEL FORBIDDEN FUNCTIONS CHECK $RESET"

OBJS=$(find ../../ -type f -name "*.o")

for OBJ in $OBJS
do
 base_name=$(basename $OBJ)
 config_name=$(find forbidden_config -type f -name "${base_name%.o}.config")
 echo -ne "$BMAG $base_name $RESET"
 extra_cmd="| grep -v ft_"
 bash ./forbidden_tester/forbidden.sh $OBJ $config_name "$extra_cmd"
done


