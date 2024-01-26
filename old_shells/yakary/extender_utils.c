#include "../include/minishell.h"

//function, length_of_variable, calculates the length of a variable name starting from a given position in the input string n. It assumes that the variable name starts at index 1 in the string 'n' (i.e., after the initial '$' character). The function stops counting characters when it encounters a character that is not alphanumeric or an underscore ('_').

int length_of_variable(const char *n)
{
	int	i;

	i = 1;
	if (n[i] == '?')
		return (2);
	while (ft_isalnum(n[i]) || n[i] == '_')
		i++;
	return (i);
}

//function if_has checks if a given character 'c' is present in the string n. If the character is found, the function returns 1; otherwise, it returns 0. Works like strchr

int if_has(const char *n, char c)
{
	if (!n)
		return (0);
	while (*n)
	{   
		if (*n == c)
			return (1);
		n++;
	}
	return (0);
}

//function, substring_concatenation, searches for the first occurrence of the character $ in the provided string (string). When it finds the $ character or reaches the end of the string, it extracts a substring from the beginning of the string up to the position of the first $. The extracted substring is then stored in the pointer pntr. The function returns the index of the first $ character in the string.

int	substring_concatenation(char *string, char **pnt)
{
	int	i;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	*pnt = ft_substr(string, 0, (size_t)i);
	return (i);
}
