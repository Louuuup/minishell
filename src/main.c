#include "minishell.h"

//the function that aims to extract and split the directories listed in the PATH environment variable

char	**path_getter(t_data *pnt, int i)
{
	char	**result;
	char	*found;

	while (pnt->env[i++])
	{
		found = ft_strstr(pnt->env[i], "PATH=");
		if (found)
			break ;
	}
	if (!pnt->env[i])
		return (NULL);
	result = ft_split(found, ':');
	if (!result)
		return (error_out(pnt, 1), NULL);
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

// int	main(int argc, char *argv[], char **env_p)
// {
// 	t_data *data;
	
// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		(ft_putstr_fd("Error: too many arguments\n", 2));
// 		return (2);
// 	}
// 	data = get_data();
// 	env_init(data, env_p);
// 	built_env(data, 1);
// 	printf("\n\nstr is %s.\n", ft_get_env("PATH", data->env));
// 	char *str = "cat";
// 	printf("path for <%s> is %s.\n", str, cmd_fullpath(data, str));
// 	// prompt_create(data);
// 	// while (TRUE)
// 	// {
// 	// 	if (tokener(data) == 0 && extender(data) == 0 && parser(data))
// 	// 		exec_main(data);
// 	// }
// 	free_all(data);
//     return (0);
// }

int	main(int argc, char *argv[], char **env_p)
{
	t_data pnt;
	
	(void)argv;
	if (argc != 1)
	{
		(ft_putstr_fd("Error: too many arguments\n", 2));
		return (2);
	}
	init_pntr(&pnt, env_p);
	while (TRUE)
	{
		set_mode(&pnt, INTERACT);
		// pnt.input = readline("minishell42$ ");
		set_mode(&pnt, NON_INTERACT);
		if (global_signal == 1 && global_signal--)
			pnt.code_exit = 130;
		if (!pnt.input)
			built_exit(&pnt, NULL);
		// if (pnt.input[0] != '\0')
		// 	add_history(pnt.input);
		pnt.path = path_getter(&pnt, -1);
		if (tokener(&pnt) == 0 && extender(&pnt) == 0 && parser(&pnt))
			alt_exec_main(&pnt);
	}
    return (0);
}