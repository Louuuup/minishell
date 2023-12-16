#include "minishell.h"

void env_init(t_data *data, char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof(char *));
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
	while (1)
	{
		if (tokener(data) == 0 && extender(data) == 0 && parser(data))
			write(1, "Hoho!", 5);
	}
    return (0);
}
