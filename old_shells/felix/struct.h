
#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"
# include <unistd.h>
# include <stdbool.h>

enum e_redir_type
{
	REDIR_NONE, 	//stdin stdout
	REDIR_INPUT,	// <
	REDIR_OVERWRITE,// >
	REDIR_APPEND,	// >>
	REDIR_HEREDOC,	// <<
	REDIR_PIPE		// |
};

enum e_error_list
{
	FAILURE,
	SUCESS,
	MALLOC_FAIL,
};

typedef struct s_cmd
{
	char			**cmd;
	char			*token;
	int				index;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int 			in_type;
	int				out_type;
	char 			*infile;
	char			*outfile;
	int				check;
	struct s_cmd	*next;
	bool			built_in;
}			t_cmd;

typedef struct s_info
{
	t_cmd			*cmd_list;
	t_cmd			*head;
	int				cmd_count;
	char 			**new_env;
	char			**env;
}			t_info;

int	ft_initstruct(t_info *info, char **envp);

#endif
