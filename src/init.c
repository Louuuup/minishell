#include "minishell.h"

void	shlvl(t_data *data)
{
	char	*shlvl;
	int		lvl;

	shlvl = get_var(data->env, "SHLVL");
	if (shlvl)
	{
		lvl = ft_atoi(shlvl);
		lvl++;
		shlvl = ft_itoa(lvl);
		set_var(data->env, "SHLVL", shlvl);
		free_null(shlvl);
	}
	else
		set_var(data->env, "SHLVL", "1");
}
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
	shlvl(data);
}
