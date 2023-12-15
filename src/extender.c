#include "../include/minishell.h"

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
			var += function_replace_dollar(var, &buffer, pntr, j);
		else
			var += function_concatinate_chars(var, &buffer);
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
