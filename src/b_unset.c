#include "minishell.h"

static int	unset_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	env_removeline(t_data *data, char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (data->env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(str, data->env[i], ft_strlen(str)) != 0)
		{
			new_env[j] = data->env[i];
			j++;
		}
		else
		{
			// free(data->env[i]); // not working, crashing... why?
		}
		i++;
	}
	free(data->env);
	data->env = new_env;
}

void	built_unset(char **args, int argc, t_data *data)
{
	int	i;

	i = 1;
	while(i < argc)
	{
		if (unset_valid(args[i]) == FALSE)
			my_error(ERR_UNSET);
		else if (var_in_env(args[i]) == TRUE)
			env_removeline(data, args[i]);
		else
			printf("not in env\n");
		i++;
	}
}
