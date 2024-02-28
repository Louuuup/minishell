
MUTE = @
NAME = minishell
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------SOURCES-------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
SRC := \
	main.c	error_handler.c init.c	garbage_handler.c \
	t_utils.c	utils.c  tmp.c  garbage_tools.c
SRC += \
	exec_main.c	exec_utils.c \
	builtin_cd.c builtin_env.c	builtin_echo.c builtin_export.c builtin_utils.c \
	builtin_unset.c #builtin_exit.c
SRC += \
	parsing_main.c tokenizer.c split_tok.c count_tok.c split_tok_utils.c token_id.c \
	linked_utils.c parsing_utils.c pipe_parsing.c ft_freeparse.c expansion.c \
	removequotes.c doclist.c parsingerror.c tok_sort.c tok_sort_doc.c tok_sort2.c \
	expcat_utils.c exp_utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))
#==============================================================================#
SRC_DIR     := src
BIN_DIR     := bin
INC_DIR     := include
LIB_DIR     := lib
# RL_DIR		= include/readline to delete once changed
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_DIR   := $(LIB_DIR)/libft
#Shell cmd

CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -Ofast -g #-fsanitize=address
MKDIRP := mkdir -p
DELETE := rm -rf
# headers to include
INCLUDES := -I$(LIBFT_DIR) -I$(INC_DIR)
# things to link
#
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#--------------------------------RL VARIABLES----------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
# DIRECTORIES
READLINE_DIR			:= $(LIB_DIR)/readline
READLINE_SRC_DIR 		:= $(READLINE_DIR)/src #(build)
READLINE_INSTALL_DIR 	:= $(READLINE_DIR)/install
# PATHS
READLINE_URL			:= https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
READLINE_SRC			:= $(READLINE_DIR)/readline-8.2.tar.gz
READLINE_INSTALLED		:= $(READLINE_DIR)/.installed
# ADDONS
INCLUDES 				+= -I$(READLINE_INSTALL_DIR)/include
LIBRL 					:= -L$(READLINE_INSTALL_DIR)/lib -lreadline -lncurses
READLINE_DEPENDENCIES	:= $(if $(wildcard $(READLINE_INSTALLED)),,install_readline)

#==============================================================================#
LFLAGS :=  $(LIBFT) $(LIBRL) #librl to re-see

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------MAIN RULES----------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
all: $(READLINE_DEPENDENCIES) libft $(NAME)
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(MUTE)echo "$(BLUE)$(BOLD)✅Compiling $(PURPLE)MINISHELL $(BLUE)→ $(RESET)$(CYAN)$(notdir $<)        $(RESET)"
	$(MUTE)$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	$(MUTE)printf	$(UP)$(CUT)
$(NAME): $(BIN_DIR) $(OBJS) $(READLINE_DEPENDENCIES)
	$(MUTE)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Successfully compiled $(PURPLE)MINISHELL         $(RESET)"
$(BIN_DIR):
	$(MUTE)$(MKDIRP) $(BIN_DIR)
libft:
	$(MUTE)$(MAKE) -C $(LIBFT_DIR)
bonus: all
	$(MUTE)echo "\n🤯No bonus🤯\n"
clean:
	$(MUTE)$(DELETE) $(OBJS)
	$(MUTE)$(DELETE) $(BIN_DIR)
	$(MUTE)$(MAKE) -C $(LIBFT_DIR) clean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Cleaned $(PURPLE)MINISHELL$(RESET)"
fclean: clean
	$(MUTE)$(DELETE) $(NAME)
	$(MUTE)$(MAKE) -C $(LIBFT_DIR) fclean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Fully cleaned $(PURPLE)MINISHELL$(RESET)"
rclean:
	$(MUTE)$(DELETE) $(READLINE_DIR)
ffclean: fclean rclean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Fully Fully cleaned $(PURPLE)MINISHELL$(RESET)"
PDF		:= minishell_en.pdf
GIT_URL := https://github.com/Louuuup/minishell
PDF_URL := $(GIT_URL)/instructions/minishell_en.pdf
OS		:= $(shell uname -s)
re: fclean all
.PHONY: all clean fclean re libft bonus
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------------RUN--------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
run: all
	./minishell
val: all cp
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=/tmp/supp.txt ./minishell
cp: #copies supp.txt to root/tmp.
	cp debug/supp.txt /tmp
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------READLINE RULES---------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
install_readline: $(READLINE_INSTALLED)

readline:
	if -f ["$(READLINE_INSTALLED)"]; then \
		$(MUTE)echo "READLINE INSTALLED"; \
	else \
		$(MUTE)echo "READLINE NOT INSTALLED"; \
		$(MUTE)install_readline; \
		$(MUTE)touch $(READLINE_INSTALLED) \
	fi

$(READLINE_INSTALLED):
	$(MUTE)$(MKDIRP) $(READLINE_DIR)
	$(MUTE)echo "$(CYAN)Downloading and installing readline...$(RESET)"
#	$(MUTE)echo "$(CYAN)Installing from $(YELLOW)$(READLINE_URL) $(CYAN)to $(YELLOW)$(READLINE_SRC)"
	$(MUTE)if [ ! -f $(READLINE_SRC) ]; then \
		curl -# -o $(READLINE_SRC) $(READLINE_URL); \
	fi
	$(MUTE)mkdir -p $(READLINE_SRC_DIR)
	$(MUTE)tar -xf $(READLINE_SRC) -C $(READLINE_SRC_DIR) --strip-components=1
	$(MUTE)cd $(READLINE_SRC_DIR) && \
	./configure --prefix=$(PWD)/$(READLINE_INSTALL_DIR) && \
	clear && echo "$(BOLD)$(CYAN)readline$(RESET) is now being built" && \
	make --quiet && \
	clear && echo "$(BOLD)$(CYAN)readline$(RESET) is now being installed" && \
	make install --quiet
	$(MUTE)printf "$(TOP_LEFT)$(ERASE_ALL)"
	$(MUTE)echo "[$(BOLD)$(PURPLE)readline$(RESET)] \
	installed locally in $(CYAN)$(UNDERLINE)$(READLINE_DIR)$(RESET)"
	$(MUTE)touch $@

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------------PDF--------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
pdf:
	@curl -# -L $(PDF_URL) -o $(PDF)
ifeq ($(OS),Darwin)
	@open $(PDF)
else
	@xdg-open $(PDF) || echo "Please install a compatible PDF viewer"
endif
	@sleep 2
	@rm -f $(PDF)
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#------------------------------------NORM--------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
norm: all
	norminette
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------------HELP-------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
help man:
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"
	$(MUTE)echo "$(BOLD)$(YELLOW)                       Welcome to $(PURPLE)$(BOLD)MINISHELL                         $(RESET)"
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(CYAN) Available Options:$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)  make (all)$(RESET)    - Compile the main program and dependencies"
	$(MUTE)echo "$(BOLD)  make run$(RESET)      - Compiles and runs the ./minishel program"
	$(MUTE)echo "$(BOLD)  make clean$(RESET)    - Remove compiled object files"
	$(MUTE)echo "$(BOLD)  make fclean$(RESET)   - Remove compiled files and executable"
	$(MUTE)echo "$(BOLD)  make rclean$(RESET)   - Remove the local readline library"
	$(MUTE)echo "$(BOLD)  make re$(RESET)       - Remove all compiled files and recompile"
	$(MUTE)echo "$(BOLD)  make pdf$(RESET)      - Download and open the project PDF"
	$(MUTE)echo "$(BOLD)  make norm$(RESET)     - Run norminette for coding style"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(CYAN) Debug Options:$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)  make libft$(RESET)    - Compile only the library"
	$(MUTE)echo "$(BOLD)  make readline$(RESET) - Install Readline library locally"
	$(MUTE)echo "$(BOLD)  make val$(RESET)      - $(BOLD)make run $(RESET)but with a flagged Valgrind"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------COLOR CODES---------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
# Colors
BLACK		=\033[30m
RED			=\033[31m
GREEN       =\033[32m
YELLOW      =\033[33m
BLUE        =\033[34m
PURPLE      =\033[35m
CYAN        =\033[36m
WHITE       =\033[37m
# Text
ERASE       =\033[2K
RESET       =\033[0m
BOLD        =\033[1m
FAINT       =\033[2m
ITALIC      =\033[3m
UNDERLINE   =\033[4m
INVERT      =\033[7m
STRIKE      =\033[9m
# Background
BG_BLACK    =\033[40m
BG_RED      =\033[41m
BG_GREEN    =\033[42m
BG_YELLOW   =\033[43m
BG_BLUE     =\033[44m
BG_PURPLE   =\033[45m
BG_CYAN     =\033[46m
BG_WHITE    =\033[47m
# Others
UP    ="\033[A" # cursor up
CUT   ="\033[K" # cut line
#==============================================================================#
