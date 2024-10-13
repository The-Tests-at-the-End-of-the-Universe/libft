usage() {
	cat <<EOF
Usage: $0 [options] [--] [file...]

Arguments:

  -h, --help
	Display this usage message and exit.

  -nm, --no-memory
	This flag will disable the memory tests run in this tester.
	This flag does not work with all no flags selected

  -nn, --no-norminette
	This flag will disable the norminette tests run in this tester.

  -nf, --no-forbidden
	This flag will disable the forbidden function tests run in this tester.

  -c <"arr">, --cases <"arr">
	This flag passes together with an array of strings will only test
	the cases that are passed. It is used as follows
	bash tester.sh -c "ft_strrchr ft_strjoin ft_strlen"

  -b, --bonus
  	This flag will run the bonus tests as well

EOF
}

# handy logging and error handling functions
log() { printf '%s\n' "$*"; }
error() { log "ERROR: $*" >&2; }
fatal() { error "$*"; exit 1; }
usage_fatal() { error "$*"; usage >&2; exit 1; }


#colors
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

#files
err_log="logs/err.log"
mem_log="logs/mem.log"
fail_log="logs/fail.log"
rm -rf tests/$err_log
rm -rf tests/$mem_log
rm -rf tests/$fail_log
touch tests/$err_log
touch tests/$mem_log
touch tests/$fail_log
temp_err_log="logs/temp_err.log"
temp_mem_log="logs/temp_mem.log"
temp_fail_log="logs/temp_fail.log"

#variables
norminette=true
forbidden=true
memory=true
fail=false
fail_test=true
bonus=false
suppressions=utils/valgrind_suppresion
valgrind="valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --error-exitcode=42 --suppressions=$suppressions"

while [ "$#" -gt 0 ]; do
	arg=$1
	case $1 in
		# convert "--opt=the value" to --opt "the value".
		# the quotes around the equals sign is to work around a
		# bug in emacs' syntax parsing
		--*'='*)
		shift;
		set -- "${arg%%=*}" "${arg#*=}" "$@";
		continue;;
		-c|--cases)
		test_cases=$2
		check_cases=1
		shift 2
		;;
		-nm|--no-memory)
		memory=false
		shift
		;;
		-nn|--no-norminette)
		norminette=false
		shift
		;;
		-nf|--no-forbidden)
		forbidden=false
		shift
		;;
		-b|--bonus)
		bonus=true
		shift
		;;
		-h|--help)
		usage;
		exit 0
		;;
		--)
		shift;
		break
		;;
		-*)
		usage_fatal "unknown option:'$1'"
		;;
		*)
		break
		;; # reached the list of file names
	esac
done

if [[ "$bonus" == "true" ]]; then
tests=(
"ft_atoi"
"ft_bzero"
"ft_calloc"
"ft_isalnum"
"ft_isalpha"
"ft_isascii"
"ft_isdigit"
"ft_isprint"
"ft_itoa"
"ft_lstadd_back"
"ft_lstadd_front"
"ft_lstclear"
"ft_lstdelone"
"ft_lstiter"
"ft_lstlast"
"ft_lstmap"
"ft_lstnew"
"ft_lstsize"
"ft_memchr"
"ft_memcmp"
"ft_memcpy"
"ft_memmove"
"ft_memset"
"ft_putchar_fd"
"ft_putendl_fd"
"ft_putnbr_fd"
"ft_putstr_fd"
"ft_split"
"ft_strchr"
"ft_strdup"
"ft_striteri"
"ft_strjoin"
"ft_strlcat"
"ft_strlcpy"
"ft_strlen"
"ft_strmapi"
"ft_strncmp"
"ft_strnstr"
"ft_strrchr"
"ft_strtrim"
"ft_substr"
"ft_tolower"
"ft_toupper")
else
tests=(
"ft_atoi"
"ft_bzero"
"ft_calloc"
"ft_isalnum"
"ft_isalpha"
"ft_isascii"
"ft_isdigit"
"ft_isprint"
"ft_itoa"
"ft_memchr"
"ft_memcmp"
"ft_memcpy"
"ft_memmove"
"ft_memset"
"ft_putchar_fd"
"ft_putendl_fd"
"ft_putnbr_fd"
"ft_putstr_fd"
"ft_split"
"ft_strchr"
"ft_strdup"
"ft_striteri"
"ft_strjoin"
"ft_strlcat"
"ft_strlcpy"
"ft_strlen"
"ft_strmapi"
"ft_strncmp"
"ft_strnstr"
"ft_strrchr"
"ft_strtrim"
"ft_substr"
"ft_tolower"
"ft_toupper")
fi

#prep tests
git submodule init
git submodule update
make -C ../ re
libft_a=$(find ../../ -type f -name libft.a -not -path "$PWD*" | tail -1)
libft_h=$(find ../../ -type f -name libft.h -not -path "$PWD*" | tail -1)
cp $libft_a ./tests/
cp $libft_h ./tests/
make -C ./ all
rm -rf ./tests/libft.a
rm -rf ./tests/libft.h

if [[ $norminette == "true" ]]; then
(cd tests && mkdir -p norm_test)
pwd=$(pwd)
pwd=$(basename $pwd)
srcs=$(find ../  -type f -name "*.c" -not -path "../$pwd/*")
headers=$(find ../ -type f -name "*.h" -not -path "../$pwd/*")
cp $srcs ./tests/norm_test
cp $headers ./tests/norm_test
(cd norminette_tester && bash norminette_tester.sh -npi -d ../tests/norm_test)
norminette_code=$(echo $?)
if [[ $norminette_code == 1 ]]; then
	fail=true
fi
(cd tests && rm -rf norm_test)
fi
if [ "$forbidden" == "true" ]; then
(cd forbidden_func && bash check_forbidden_libft.sh)
forbidden_code=$(echo $?)
if [[ $forbidden_code == 1 ]]; then
	fail=true
fi
fi

cd tests
echo -e "${YEL}Functions${RESET}"
for test in ${tests[@]}; do

	#check to run case or not
	if [[ $check_cases == 1 ]]; then 
		case_check=${test##*/}
		if [[ $(echo ${test_cases[@]} | grep $case_check) ]]
		then
		:
		else
			continue ;
		fi
	fi

	#print function
	echo -e "${MAG}$test${RESET}"

	test_count=$((1))
	while [ 1 ]; do

	#cases
	./tester $test $test_count 1> /dev/null 2> $temp_err_log
	exit_code=$(echo $?)
	if [ $exit_code == 1 ]; then
	echo -ne "${RED}${test_count} FAIL ${RESET}"
	echo "$test===============================" >> $err_log
	cat $temp_err_log >> $err_log
	fail=true
	fi

	if [ $exit_code == 0 ]; then
	echo -ne "${GRN}${test_count} OK ${RESET}"
	fi


	#mem test
	if [ $memory == true ]; then
	$valgrind ./tester $test $test_count 2> $temp_mem_log
	mem_exit_code=$(echo $?)
	if [ $mem_exit_code == 42 ]; then
	echo -ne "${RED} MOK ${RESET}"
	echo "$test===============================" >> $mem_log
	cat $temp_mem_log >> $mem_log
	fail=true
	mem_fail=true
	fi
	fi

	#delete temp files
	rm -rf $temp_err_log
	rm -rf $temp_mem_log

	if [ $exit_code == 2 ]; then
	break
	fi
	test_count=$((test_count+1))
	done

	#fail tests
	test_count=$((1))

	if [ $fail_test == true ]; then
	echo
	while [ 1 ]; do
	$($valgrind ./tester $test $test_count "-ft" 1> /dev/null 2> $temp_fail_log) 
	fail_exit_code_ft=$(echo $?)
	$(valgrind ./tester $test $test_count "-og" 1> /dev/null 2>> $temp_fail_log) 
	fail_exit_code_og=$(echo $?)

	if [ $fail_exit_code_og == 2 ]; then
	rm -rf $temp_fail_log
	break
	fi
	
	if [ $fail_exit_code_ft == $fail_exit_code_og ]; then
	echo -ne "${GRN}${test_count} FOK ${RESET}"
	else
	echo -ne "${RED}${test_count} FKO ${RESET}"
	echo "$test===============================" >> $fail_log
	cat $temp_fail_log >> $fail_log
	fail=true
	fail_fail=true
	fi

	#delete temp files
	rm -rf $temp_fail_log

	test_count=$((test_count+1))
	done 
	echo
	fi

done

# git restore .

if [[ $fail == "false" ]]; then
	echo -e "${GRN}Congratulations all tests passed!${RESET}"
	rm -rf $mem_log
	rm -rf $err_log
	rm -rf $fail_log
	exit 0
else
	if [[ $mem_fail == "true" ]]; then
		echo -e "${RED}memory errors, check logs or use following command manually: $valgrind${RESET}"
	fi 
	if [[ $fail_fail == "true" ]]; then
		echo -e "${RED}fail errors, check fail logs ${RESET}"
	fi 
	echo -e "${RED}Not all tests passed, check logs${RESET}"
	exit 1
fi
