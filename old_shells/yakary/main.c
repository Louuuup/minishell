#include "minishell.h"

//the function that aims to extract and split the directories listed in the PATH environment variable

char	**path_getter(t_data *pnt, int i)
{
	char	**result;
	char	*found;

	while (pnt->env[++i])
	{
		found = ft_strstr(pnt->env[i], "PATH=");
		if (found != NULL)
			break ;
	}
	if (pnt->env[i] == NULL)
		return (NULL);
	result = ft_split_fd(found, ':');
	if (!result)
	{
		free(result);
		return (error_out(pnt, "ft_split", 1), NULL);
	}
	return (result);
}

//function in the minishell project of Ecole 42 is responsible for initializing the environment data in the t_data structure. It takes as input the t_data pointer (data) and an array of strings (env) representing the environment variables. (130 == CTRL+C)

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
	t_data pnt;
	// (void)argc;
	(void)argv;
	if (argc != 1)
		return (ft_putstr_int("Error: too many arguments\n", 2));
	init_pntr(&pnt, env_p);
	while (1)
	{
		set_mode(&pnt, INTERACT);
		pnt.input = readline("Yo-ho-ho!$ ");
		set_mode(&pnt, NON_INTERACT);
		if (global_signal == 1 && global_signal--)
			pnt.code_exit = 130;
		if (!pnt.input)
			built_exit(&pnt, NULL);
		if (pnt.input[0] != '\0')
			add_history(pnt.input);
		pnt.path = path_getter(&pnt, -1);
		if (tokener(&pnt) == 0 && extender(&pnt) == 0 && parser(&pnt) == 0)
			alt_exec_main(&pnt);
		pntr_cleaning(&pnt);
	}
	return (0);
}
