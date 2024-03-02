# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 15:09:39 by yakary            #+#    #+#              #
#    Updated: 2024/03/02 13:02:00 by ycyr-roy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC = ft_bzero.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_memcpy.c \
	ft_memmove.c \
    ft_memset.c \
    ft_strlen.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	get_next_line.c \
	ft_charjoinfree.c \
	ft_has_space.c \
	print_grid.c \
	ft_free.c \
	find_symbol.c \
	arr_len.c \
	arr_dup.c \
	ft_strcat.c \
	ft_strcmp.c \
	ft_split_length.c \
	ft_strstr.c \
	ft_printf_fd.c \
	ft_split_fd.c \
	ft_isspace.c
OBJS = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))
BOBJS = $(addprefix $(BIN_DIR)/, $(BSRC:.c=.o))
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -o test
LIBC = ar rc
LIBR = ranlib
RM = rm -f
RM_DIR = rm -rf
BIN_DIR = bin
VPATH = .

#COLORS
BLACK       =\033[30m
RED         =\033[31m
GREEN       =\033[32m
YELLOW      =\033[33m
BLUE        =\033[34m
PURPLE      =\033[35m
CYAN        =\033[36m
WHITE       =\033[37m
# # Text
ERASE       =\033[2K
RESET       =\033[0m
BOLD        =\033[1m
FAINT       =\033[2m
ITALIC      =\033[3m
UNDERLINE   =\033[4m
# BLINK     =\033[5m #no effect on iterm?
INVERT      =\033[7m
STRIKE      =\033[9m
# # Background
BG_BLACK    =\033[40m
BG_RED      =\033[41m
BG_GREEN    =\033[42m
BG_YELLOW   =\033[43m
BG_BLUE     =\033[44m
BG_PURPLE   =\033[45m
BG_CYAN     =\033[46m
BG_WHITE    =\033[47m
UP	="\033[A" #cursor up
CUT	="\033[K" #cut line

all: $(NAME)
$(BIN_DIR)/%.o: %.c
	@echo "$(BLUE)$(BOLD)✅Compiling $(GREEN)LIBFT $(BLUE)→ $(RESET)$(CYAN)$(notdir $<)$(RESET)        "
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(UP)$(CUT)
$(NAME): $(BIN_DIR) $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@$(LIBR) $(NAME)
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)
clean:
	@$(RM_DIR) $(BIN_DIR)
fclean: clean
	@$(RM) $(NAME)
re: fclean all
