tests=(
# "ft_atoi"
# "ft_bzero"
# "ft_calloc"
# "ft_isalnum"
# "ft_isalpha"
# "ft_isascii"
# "ft_isdigit"
# "ft_isprint"
# "ft_itoa"
# "ft_lstadd_back"
# "ft_lstadd_front"
# "ft_lstclear"
# "ft_lstdelone"
# "ft_lstiter"
# "ft_lstlast"
# "ft_lstmap"
# "ft_lstnew"
# "ft_lstsize"
# "ft_memchr"
# "ft_memcmp"
# "ft_memcpy"
# "ft_memmove"
# "ft_memset"
# "ft_putchar_fd"
# "ft_putendl_fd"
# "ft_putnbr_fd"
# "ft_putstr_fd"
# "ft_split"
# "ft_strchr"
# "ft_strdup"
# "ft_striteri"
# "ft_strjoin"
# "ft_strlcat"
# "ft_strlcpy"
# "ft_strlen"
# "ft_strmapi"
# "ft_strncmp"
# "ft_strnstr"
# "ft_strrchr"
# "ft_strtrim"
# "ft_substr"
# "ft_tolower"
"ft_toupper")

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
touch $err_log
touch $mem_log
temp_err_log="logs/temp_err.log"
temp_mem_log="logs/temp_mem.log"

#variables
norminette=true
forbidden=true
memory=true
valgrind="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42"

#prep tests
make -C ./ all

if [ norminette == true ]; then
make --no-print-directory -C tests norminette
fi
if [ forbidden == true ]; then
(cd forbidden_func && bash check_forbidden_libft.sh)
fi

cd tests
echo -e "${YEL}Functions${RESET}"
for test in ${tests[@]}; do
	#print function
	echo -e "${MAG}$test${RESET}"

	#cases
	./tester $test 1> /dev/null 2> $temp_err_log
	exit_code=$(echo $?)
	if [ exit_code != 0 ]; then
	echo "$test===============================" > $err_log
	cat $temp_err_log >> $err_log
	fi

	#mem test
	if [ memory = true ]; then
	$valgrind ./tester $test 2> $temp_mem_log
	mem_exit_code=$(echo $?)
	if [ mem_exit_code == 42 ]; then
	echo "$test===============================" >> $mem_log
	cat $temp_mem_log >> $mem_log
	fi
	fi

	#delete temp files
	rm -rf $temp_err_log
	rm -rf $temp_mem_log
done
