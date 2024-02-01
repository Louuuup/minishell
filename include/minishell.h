#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
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
# define MINISHELL_ERR "\033[31m\033[1mminiSHELL: \033[0m"
# define PROMPT_NAME "\033[35m\033[1mminiSHELL \033[0m\033[1m→ \033[0m"
# define EXPORT_PREFIX "declare -x "
//==================Structs===================//

//chainlist for allocated memory blocks (for garbage collector)
typedef struct s_memblock
{
	void				*ptr;
	struct s_memblock	*next;
}				t_memblock;

typedef struct s_cmd
{
	char			**cmd;
	char			*token;
	int				index;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int 			in_flag; //redir_flag
	int				out_flag; //redir_flag
	char 			*infile; //path to file
	char			*outfile; //path to file
	struct s_cmd	*next;
	bool			built_in;
}			t_cmd;

typedef struct s_data
{
	t_cmd		*cmd;
	char		**env; //environnement, allocated and dynamicly updated (no garbo)
	char		*user_prompt; //prompt entered by user. (no garbo)
	int			code_exit;
	t_memblock	*memblock; //head of allocated memory blocks
}				t_data;

//base for command struct can be modified if needed


//flag fo redirection

enum e_redir_type
{
	REDIR_NONE, 	//stdin stdout
	REDIR_INPUT,	// <
	REDIR_OVERWRITE,// >
	REDIR_APPEND,	// >>
	REDIR_HEREDOC,	// <<
	REDIR_PIPE		// |
};



//==================init.c===================//

void	init_all(t_data *data, char **envp);
//==================utils.c===================//

//==================t_utils.c===================//

t_data	*get_data(void);
//==================parsing_main.c===================//

int		parser(t_data *data);
int		tokener(t_data *data);
//==================exec_main.c===================//

void	exec_main(t_data *data);

//==================exec_utils.c===================//

void	exec_cmd(t_data *data);
int		ft_pipe(t_cmd *cmd);
int		ft_dup2(t_cmd *cmd);
//==================garbage_handler.c===================//

//works like malloc but adds the pointer to the memblock list
void		*gc_malloc(size_t size);
//works like calloc but adds the pointer to the memblock list
void		*gc_calloc(size_t count, size_t size);
//adds a block on top of the list
t_memblock	*memblock_add(t_memblock *memblock, void *ptr);
//frees all the blocks in the list
void		gc_free(t_memblock *memblock);

//==================error_handler.c===================//
int		shell_error(void);
int		error_str(char *str);

#endif
