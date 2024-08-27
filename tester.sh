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
rm -rf tests/$err_log
rm -rf tests/$mem_log
touch tests/$err_log
touch tests/$mem_log
temp_err_log="logs/temp_err.log"
temp_mem_log="logs/temp_mem.log"

#variables
norminette=true
forbidden=true
memory=true
fail=false
bonus=false
suppressions=utils/valgrind_suppresion
valgrind="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 --suppressions=$suppressions"

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
make -C ./ all

if [[ $norminette == "true" ]]; then
make --no-print-directory -C tests norminette
fi
if [ "$forbidden" == "true" ]; then
(cd forbidden_func && bash check_forbidden_libft.sh)
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

	#cases
	./tester $test 1> /dev/null 2> $temp_err_log
	exit_code=$(echo $?)
	if [ $exit_code != 0 ]; then
	echo "$test===============================" >> $err_log
	cat $temp_err_log >> $err_log
	fail=true
	fi

	#mem test
	if [ $memory == true ]; then
	$valgrind ./tester $test 2> $temp_mem_log
	mem_exit_code=$(echo $?)
	if [ $mem_exit_code == 42 ]; then
	echo -ne "${RED} MOK${RESET}"
	echo "$test===============================" >> $mem_log
	cat $temp_mem_log >> $mem_log
	fail=true
	mem_fail=true
	fi
	fi

	#delete temp files
	rm -rf $temp_err_log
	rm -rf $temp_mem_log
	echo
done

if [[ $fail == "false" ]]; then
	echo -e "${GRN}Congratulations all tests passed!${RESET}"
	rm -rf $mem_log
	rm -rf $err_log
else
	if [[ $mem_fail == "true" ]]; then
		echo -e "${RED}memory errors, check logs or use following command manually: $valgrind${RESET}"
	fi 
	echo -e "${RED}Not all tests passed, check logs${RESET}"
fi

