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

	(void)argv;
	if (argc != 1)
	{
		(ft_putstr_fd("Error: too many arguments\n", 2));
		return (2);
	}
	data = get_data();
	env_init(data, env_p);
	prompt_create(data);
	while (TRUE)
	{
		if (tokener(data) == 0 && extender(data) == 0 && parser(data))
			exec_main(data);
	}
    return (0);
}
