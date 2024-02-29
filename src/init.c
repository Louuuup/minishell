#include "minishell.h"

void	init_all(t_data *data, char **envp)
{
	if (DEBUG_ON)
		printf("(init_all) start\n");
	data->env = envp;
	data->code_exit = 0;
}
