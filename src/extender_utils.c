#include "../include/minishell.h"

//finds the length of variables

int length_of_variable(char *n)
{
	int	i;

	i = 1;
	if (n[i] == '?')
		return (2);
	while (ft_isalnum(n[i]) || n[i] == '_')
		i++;
	return (i);
}

//auxiliary func, works like strchr

int if_has(const char *n, char c)
{
	if (!n)
		return (0);
	while (*n)
	{   if (*n == c)
			return (1);
	}
	return (0);
}

//it uses a string & a double pointer & returns the length of the part
//of the string till the 1st occurrence of '$'. Then assign the part
//to the first argument

int	substring_concatenation(char *string, char **pntr)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	*pntr = ft_substr(string, 0, (size_t)i);
	return (i);
}