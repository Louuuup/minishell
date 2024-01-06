#include "minishell.h"

//the code checks whether a given string (word) starts with a specified prefix (start)

// int	begin_with(const char *word, const char *start)
// {
// 	if (!word || !start)
// 		return (0);
// 	while (*start && (*start == *word))
// 	{
// 		start++;
// 		word++;
// 	}
// 	return (*start == '\0');
// }

//the function searches for a specific environment variable (name) in the array of environment variables (ev). It returns the index of the variable if found and -1 if the variable is not present in the array

// int	search_variable(char **ev, char *name)
// {
// 	int	i;

// 	i = 0;
// 	while (ev[i])
// 	{
// 		if (ev[i][ft_strlen(name)] == '=' && substring_beginning(ev[i], name))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

//the code adds a new environment variable with a specified key and value to the env array in a t_data structure

int	create_env_var(t_data *pntr, char *key, char *keep)
{
	int		i;
	char	*buff;
	char	*new_env_var;
	char	**new_env_array;
	int		size;

	buff = ft_strcat(key, "=");
	if (buff == NULL)
		return (2);
	new_env_var = ft_strcat(buff, keep);
	free(buff);
	if (new_env_var == NULL)
		return (2);
	size = ft_split_length(pntr->env);
	new_env_array = (char **)ft_calloc(sizeof(char *), size + 2);
	if (new_env_array == NULL)
		return (free(new_env_var), 2);
	i = -1;
	while (size > ++i)
		new_env_array[i] = pntr->env[i];
	new_env_array[i++] = new_env_var;
	new_env_array[i] = NULL;
	free(pntr->env);
	pntr->env = new_env_array;
	return (0);
}

//the functionis is designed to increment the value of the 'SHLVL' environment variable

int	increase_shlvl(t_data *pntr)
{
	int		shlvl;
	int		curr;
	char	*new_shlvl;
	char	*new_value;

	shlvl = variable_index(pntr->env, "SHLVL");
	if (shlvl == -1)
		return (create_env_var(pntr, "SHLVL", "1"));
	curr = ft_atoi(pntr->env[shlvl] + 6);
	if (curr == 0)
		return (1);
	new_value = ft_itoa(curr + 1);
	if (new_value == NULL)
		return (1);
	new_shlvl = ft_strcat("SHLVL=", new_value);
	free(new_value);
	if (new_shlvl == NULL)
		return (1);
	free(pntr->env[shlvl]);
	pntr->env[shlvl] = new_shlvl;
	return (0);
}
