#include "minishell.h"

//the code checks whether a given string (string) starts with a specified prefix (begin)

int	begin_with(const char *word, const char *start)
{
	if (!word || !start)
		return (0);
	while (*start && (*start == *word))
	{
		start++;
		word++;
	}
	return (*start == '\0');
}

//the function searches for a specific environment variable (name) in the array of environment variables (envp). It returns the index of the variable if found and -1 if the variable is not present in the array

int	search_variable(char **ev, char *name)
{
	int	i;

	i = 0;
	while(ev[i])
	{
		if (begin_with(ev[i], name) && ev[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

//the functionis is designed to increment the value of the 'SHLVL' environment variable

int	increase_shlvl(t_data *pntr)
{
	int		shlvl;
	int		curr;
	char	*new_shlvl;
	char	*new_value;

	shlvl = search_variable(pntr->env, "SHLVL");
}