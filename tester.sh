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

mem_log="logs/mem.log"
temp_err_log="logs/error_log.txt"
temp_mem_log="logs/temp_mem.log"
valgrind="valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42"
make -C ./ all
cd tests

echo -e "${YEL}Functions${RESET}"
for test in ${tests[@]}; do
	echo -e "${MAG}$test${RESET}"
	./tester $test 1> /dev/null 2> $temp_err_log
	exit_code=$(echo $?) 
	cat $temp_err_log
	$valgrind ./tester $test 2> $temp_mem_log
	mem_exit_code=$(echo $?)
	if [ mem_exit_code == 42 ]; then
	cat $temp_mem_log >> $mem_log
	mem_exit_code=0
	fi
	rm -rf $temp_err_log
	rm -rf $temp_mem_log
done
