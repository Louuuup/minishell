
#include "../include/minishell.h"

int env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**unset_var(t_info *inf, int unset_index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (!(new_env = malloc(env_len(inf->env) * sizeof(char *))))
		return (NULL);
	while (inf->env[i])
	{
		if (i == unset_index)
		{
			if ((inf->env[unset_index + 1]))
				i++;
			else
				break;
		}
		new_env[j] = ft_strdup(inf->env[i]);
		i++;
		j++;		
	}
	ft_free(inf->env);
	new_env[j] = NULL;
	return (new_env);
}

int	env_finder(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && (env[i][j] != str[0]))
			j++;
		if (ft_strncmp(env[i], str, (ft_strlen(str))) == 0)
		{
			if(env[i][(ft_strlen(str))] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

int ft_unset(t_info *inf)
{
    int i;
    int j;

    i = 1;
    if (!inf->cmd_list->cmd[1] || !inf->env)
        return(SUCESS);
    while(inf->cmd_list->cmd[i])
    {
        j = env_finder(inf->cmd_list->cmd[i], inf->env);
        if (0 <= j)
            inf->env = unset_var(inf, j);
        i++;
    }
	i = 0;
	return (0);
}