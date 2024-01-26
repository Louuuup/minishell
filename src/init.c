#include "minishell.h"

void	init_all(t_data *data, char **envp)
{
	data->env = envp;
	data->code_exit = 0;
}
