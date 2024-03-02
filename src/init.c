#include "minishell.h"

void	init_all(t_data *data, char **envp)
{
	int i;

	i = 0;
	if (DEBUG_ON)
		printf("(init_all) start\n");
	data->env = gc_calloc(arr_len(envp) + 1, sizeof(char *));
	while (envp[i])
	{
		data->env[i] = gc_strdup(envp[i]);
		i++;
	}
	data->code_exit = 0;
}
