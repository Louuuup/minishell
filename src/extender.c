#include "../include/minishell.h"

//it test the beginning of a string whether it starts
//with the substring we need

int	substring_beginning(char *word, char *start)
{
	int	i;

	i = 0;
	if (!word)
		return (0);
	while (start[i] && word[i] && start[i] == word[i])
		i++;
	return (start[i] == '\0');
}

//it looks for a variable in the environment variables array
//then returns the index of it or -1

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

//it get the value of variable from the data struct

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

//the func change '$' with the variable value

int	dollar_replacement(char *string, char **value, t_data *pntr, int exception)
{
	int		length = length_of_variable(string);
	char	*value_buffer;
	char	*key;

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

//the func spreads a local token with replacement of '$'
//with the value from 'data' struct

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

// the func if there is an exception in the data structure

int	if_exception(t_data *pntr, int i)
{
	return (pntr->tokens[i].type == WORD && pntr->tokens[i + 1].type != WORD
		&& pntr->tokens[i].no_space && ft_strlen(pntr->tokens[i].value) == 1
		&& pntr->count_token > (i + 1));
}

// what if we have "$" or "?" inside of a token? we need replace
// key with exception the func extends tokens after checking variables

int	extender(t_data *pntr)
{
	int	exception;
	int	stop;
	int	i;

	stop = pntr->count_token;
	i = 0;
	while (i < stop)
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
			exception = if_exception(pntr, i);
			if (token_expansion(pntr->tokens[i].value, pntr, i, exception) == 2)
				return (2);
		}
		i++;
	}
	return (0);
}
