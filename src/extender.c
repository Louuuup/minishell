#include "../include/minishell.h"

//The substring_beginning function in the  project is designed to check whether the string start is a substring that appears at the beginning of the string word

int	substring_beginning(char *word, char *start)
{
	if (!word)
		return (0);
	while (*start && *word && *start == *word)
	{
		start++;
		word++;
	}
	return (*start == '\0');
}

//function, variable_index, is designed to find the index of an environment variable in the given array of environment strings (env). It searches for a variable with a name matching the provided string n and returns the index of the matching variable in the array.

int	variable_index(char **env, char *n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][ft_strlen(n)] == '=' && substring_beginning(env[i], n))
			return (i);
		i++;
	}
	return (-1);
}

//function value_of_variable is responsible for retrieving the value of a given environment variable from the environment variable array (pntr->env)

char	*value_of_variable(t_data *pntr, char *i)
{
	int	j;

	if (ft_strcmp(i, "?") == 0)
		return (ft_itoa(pntr->code_exit));
	j = variable_index(pntr->env, i);
	if (j == -1)
		return (NULL);
	return (ft_strdup(pntr->env[j] + ft_strlen(i) + 1));
}

//The dollar_replacement function is responsible for replacing a variable reference (starting with '$') with its corresponding value in the given string

int	dollar_replacement(char *string, char **value, t_data *pntr, int exception)
{
	int		length;
	char	*value_buffer;
	char	*key;

	length = length_of_variable(string);
	if (exception && length == 1)
		return (*value = ft_strdup(""), length);
	if (length == 1)
		return (*value = ft_strdup("$"), length);
	key = ft_substr(string, 1, length - 1);
	if (key == NULL)
		return (length);
	value_buffer = value_of_variable(pntr, key);
	free(key);
	if (value_buffer == NULL)
		*value = ft_strdup("");
	else
		*value = ft_strdup(value_buffer);
	free(value_buffer);
	return (length);
}

//The token_expansion function handle the expansion of tokens in a shell, specifically focusing on replacing variables prefixed with the '$' symbol.

int	token_expansion(char *var, t_data *pntr, int i, int j)
{
	char	*buffer;
	char	*result;
	char	*buffer_result;
	char	*buffer_value;

	result = NULL;
	buffer_value = var;
	while (*var)
	{
		buffer = NULL;
		if (*var == '$')
			var += dollar_replacement(var, &buffer, pntr, j);
		else
			var += substring_concatenation(var, &buffer);
		if (buffer == NULL)
			return (free(result), 2);
		buffer_result = ft_strcat(result, buffer);
		(free(buffer), free(result));
		if (buffer_result == NULL)
			return (2);
		result = buffer_result;
	}
	free(buffer_value);
	pntr->tokens[i].value = result;
	return (0);
}

// the func checks if there is an exception in the data structure

int	check_exception(t_data *pntr, int i)
{
	return (pntr->tokens[i].type == WORD && pntr->tokens[i + 1].type != WORD
		&& pntr->tokens[i].no_space && ft_strlen(pntr->tokens[i].value) == 1
		&& pntr->count_token > (i + 1));
}

//The extender function is a part of the tokenization process in a shell program, specifically handling token expansion

int	extender(t_data *pntr)
{
	int	exception;
	int	i;

	i = 0;
	while (i < pntr->count_token)
	{
		if (pntr->tokens[i].type == REDIRECT_MULTILINE)
		{
			i += 2;
			while (pntr->tokens[i].no_space)
				i++;
		}
		if (if_has(pntr->tokens[i].value, '$')
			&& (pntr->tokens[i].type == DQUOTE || pntr->tokens[i].type == WORD))
		{
			exception = check_exception(pntr, i);
			if (token_expansion(pntr->tokens[i].value, pntr, i, exception) == 2)
				return (2);
		}
		i++;
	}
	return (0);
}
