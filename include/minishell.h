#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline.h>
# include <history.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>

//==================VALUES===================//
# define DEBUG_ON 0
# define TRUE 1
# define FALSE 0
# define YES 1
# define NO 0
# define PROMPT_NAME "\033[35m\033[1mminiSHELL \033[0m\033[1m→ \033[0m"
# define EXPORT_PREFIX "declare -x "
//==================ERRORS===================//
# define ERR_MAIN "\033[31m\033[1mERROR > \033[0m"
# define ERR_EXP "\033[37m\033[1mREASON\033[0m"
# define ERR_FORK "Forked up!\n"
# define ERR_ALLOC "Allocation error\n"
# define ERR_PIPE "Couldn't open the pipe\n"
# define ERR_DUP "Dup error\n"
# define ERR_CD_ARGS "Too much arguments for CD\n"
# define ERR_CD "Invalid name or path\n"
# define ERR_EXPORT "Invalid identifier for export\n"
# define ERR_UNSET "Invalid indentifier for unset\n"
# define ERR_WRITE "Write error\n"
//==================Structs===================//

typedef struct s_data
{
	char	**env;
	int		code_exit;
}				t_data;

#endif
