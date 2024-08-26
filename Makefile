# GNL_TEST_DIR = get_next_line/tests
# PRINTF_TEST_DIR = ft_printf/tests
LIBFT_TEST_DIR = libft

.SILENT:

all:  LIBFT #PRINTF GNL

LIBFT:
	@$(MAKE) --no-print-directory -C $(LIBFT_TEST_DIR) all
	@$(MAKE) --no-print-directory -C $(LIBFT_TEST_DIR) fclean
	(cd forbidden_func && bash check_forbidden_libft.sh)

# PRINTF:
# 	cp -R ../src/ft_printf ./
# 	@$(MAKE) --no-print-directory -C $(PRINTF_TEST_DIR)
# 	rm -rf ft_printf

# GNL:
# 	cp -R ../src/get_next_line	./
# 	@$(MAKE) --no-print-directory -C $(GNL_TEST_DIR)
# 	rm -rf get_next_line
	
fclean: 
	rm -rf printf
	rm -rf get_next_line