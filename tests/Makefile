include ./config.mk

LIBFT_A = libft.a

WELCOME = libft_tester_welcome.c

TESTER = libft_tester.c

TEST_EXE = tester

TEST_DIR = libft_tests

SOURCES     := $(shell find $(SRCDIR) -type f -name "*.c")

NORMINETTE = norminette_tester.sh
NORM_NO_PR = -npi


all: test

.SILENT:

test: libft logs welcome tests


tests:
	cc -Wall -Werror -Wextra -o tester $(TESTER) $(TEST_DIR)/*.c $(LIBFT_A) -lbsd  -g
	rm -rf $(LIBFT_A)

norminette:
	cd ../norminette_tester && bash $(NORMINETTE) $(NORMDIR)

welcome:
	cc -Wall -Werror -Wextra $(WELCOME) && ./a.out
	rm -rf a.out

logs:
	mkdir -p logs

libft:
	@$(MAKE) -C $(LIBFT) all
	cp $(LIBFT)/lib/$(LIBFT_A) ./
	@$(MAKE) -C $(LIBFT) fclean

fclean:
	rm -rf $(LIBFT_A)
	rm -rf logs
	rm -rf $(TEST_EXE)

re:	fclean all