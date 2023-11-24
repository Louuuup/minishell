#include "minishell.h"

void env_init(t_data *data, char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	data->env = ft_calloc(i, sizeof(char *) + 1);
	i = 0;
	while(env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char **env_p)
{
	t_data *data;

	(void)argc;
	(void)argv;
	data = get_data();
	env_init(data, env_p);
	prompt_create(data);
    return (0);
}

