#include "../../include/minishell.h"

int check_arguments(t_type_token type)
{
	if (type == SQUOTE || type == DQUOTE || type == WORD)
		return (1);
	return (0);
}

int check_if_redirection(t_type_token type)
{
	if (type == WORD || type == SQUOTE || type == DQUOTE || type == PIPE)
		return (1);
	return (0);
}

int	count_pipes(t_data *pointer)
{
	int	i, j;

	j = -1;
	i = 0;
	while (++i < pointer->count_token)
		if (pointer->tokens[i].type == PIPE)
			j++;
	return (j);
}

int	new_tokens_count(t_data *pointer)
{
	int i, j, k;

	i = 0;
	k = 0;
	while (i < pointer->count_token)
	{
		if (pointer->tokens[i].type == WORD)
		{
			j = 0;
			while (pointer->tokens[i].value[j])
			{
				if (pointer->tokens[i].value[j] == ' ')
					k++;
				j++;
			}
		}
		i++;
		k++;
	}
	return (k);
}