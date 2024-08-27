#Compiler and Linker
CC          := cc

#The Target Binary Program
TARGET      := tester

#The Directories, Source, Includes, Objects, Binary and Resources
WELCOME     := libft_tester_welcome.c
LIBFT       := ../../
SRCDIR      := ./libft_tests
INCDIR      := ./
OBJDIR      := ./build/obj
TARGETDIR   := .
BUILDIR     := ./build
SRCEXT      := c
OBJEXT      := o
NORMDIR     := -d ../tests/norm_test
NORMINETTE = norminette_tester.sh

#Flags, Libraries and Includes
CFLAGS      := -I./ -Wall -Werror -Wextra 


#---------------------------------------------------------------------------------
#DO NOT EDIT BELOW THIS LINE
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#Default Make

all: build libft logs welcome $(TARGETDIR)/$(TARGET) 

#Remake
re: fclean all

#Make the Directories
build:
	@mkdir -p $(OBJDIR)

welcome:
	cc -Wall -Werror -Wextra $(WELCOME) && ./a.out
	rm -rf a.out

norminette:
	mkdir -p norm_test
	cp -r ../../*.c norm_test
	-(cd ../norminette_tester && bash $(NORMINETTE) $(NORMDIR))
	rm -rf norm_test 

#Clean only Objects
clean:
	@$(RM) -rf $(OBJDIR)

#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(BUILDIR)
	@$(RM) -rf $(TARGET)
	@$(RM) -rf logs

logs:
	mkdir -p logs

#Link
$(TARGETDIR)/$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) -o  $(TARGETDIR)/$(TARGET)

#Compile
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

#LIBFT
libft:
	@$(MAKE) -C $(LIBFT) all
	/bin/cp -rf ../../libft.a ./
	@$(MAKE) -C $(LIBFT) fclean


#Non-File Targets
.PHONY: all re clean fclean

.SILENT: