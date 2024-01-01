

NAME = minishell
#==============================================================================#
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wunreachable-code -Ofast -g -fsanitize=address
SRC = main.c	utils.c		t_utils.c	prompt.c	builtin.c	exec_utils.c \
		b_cd.c	b_echo.c	b_env.c		b_export.c	b_env_print.c	tokener.c \
		parser.c	parser_utils.c	tokener_filling.c	parser_merge_words.c \
		parser_func.c	b_unset.c	b_exit.c	exec.c	extender.c \
		extender_utils.c	multiline.c	signal.c	exec_search.c
#==============================================================================#
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))
#==============================================================================#
SRC_DIR     = src
MV_DIR      = moves
BIN_DIR     = bin
INC_DIR     = include
RL_DIR		= include/readline
LIBFT_DIR   = lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBRL		= -L ./include/readline/ -lreadline -lcurses
READLINE    = $(RL_DIR)/libreadline.a
HISTORY    = $(RL_DIR)/libhistory.a
#Shell cmd
MKDIRP = mkdir -p
RM = rm -f
RM_DIR = rm -rf
#==============================================================================#
# headers to include
INCLUDES = -I$(LIBFT_DIR) -I$(INC_DIR) -I$(MV_DIR) -I$(RL_DIR)
# things to link
LFLAGS =  $(LIBFT) $(LIBRL)

#==============================================================================#
all: libft $(NAME)
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(BLUE)$(BOLD)✅Compiling $(PURPLE)MINISHELL $(BLUE)→ $(RESET)$(CYAN)$(notdir $<)        $(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf	$(UP)$(CUT)
$(NAME): $(BIN_DIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)
	@echo "$(GREEN)$(BOLD)✅ Successfully compiled $(PURPLE)MINISHELL         $(RESET)"
$(BIN_DIR):
	@$(MKDIRP) $(BIN_DIR)
libft:
	@$(MAKE) -C $(LIBFT_DIR)
bonus: all
	@echo "\n🤯No bonus🤯\n"
clean:
	@$(RM) $(OBJS)
	@$(RM_DIR) $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(GREEN)$(BOLD)✅ Cleaned $(PURPLE)MINISHELL$(RESET)"
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)$(BOLD)✅ Fully cleaned $(PURPLE)MINISHELL$(RESET)"
PDF		:= minishell_en.pdf
GIT_URL := https://github.com/Louuuup/minishell
PDF_URL := $(GIT_URL)/instructions/minishell_en.pdf
OS		:= $(shell uname -s)

#=================================PDF=========================================#
pdf:
	@curl -# -L $(PDF_URL) -o $(PDF)
ifeq ($(OS),Darwin)
	@open $(PDF)
else
	@xdg-open $(PDF) || echo "Please install a compatible PDF viewer"
endif
	@sleep 2
	@rm -f $(PDF)
#==============================================================================#
norm: all
	norminette
re: fclean all
.PHONY: all clean fclean re libft bonus
#=====================================COLORS=====================================#
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
