
#ifndef MINISHELL_H
# define MINISHELL_H

# include "execution.h"
# include "struct.h"
# include "../libft/libftps.h"
# include "builtin.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include "readline/history.h"
# include "readline/readline.h"

void	ft_builtincheck(t_cmd *cmd);
void	ft_cpyenv(char **env_cpy, char **envp);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);

//void ft_close(t_info *inf);
void ft_close(t_cmd *cmd);

/*malloc list : info.env
				readline prompt
*/

#endif