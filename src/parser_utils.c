#include "../include/minishell.h"

//the purpose of check_arguments is to provide a simple check for whether a given token type is suitable as a command argument, and it returns 1 if it is and 0 otherwise

int check_arguments(t_type_token type)
{
	return (type == SQUOTE || type == DQUOTE || type == WORD);
}

//the purpose of check_if_redirection is to provide a simple check for whether a given token type is indicative of a redirection, and it returns 1 if it is and 0 otherwise.

int check_if_redirection(t_type_token type)
{
	return (type == WORD || type == SQUOTE || type == DQUOTE || type == PIPE);
}

//the purpose of the count_pipes function is to iterate through the tokenized input and count the number of pipe symbols present. The final count is then returned.

int	count_pipes(t_data *pointer)
{
	int	i;
	int	pipeCount;

	i = -1;
	pipeCount = 0;
	while (++i < pointer->count_token)
		if (pointer->tokens[i].type == PIPE)
			pipeCount++;
	return (pipeCount);
}

//the new_tokens_count function counts the total number of tokens that would result after splitting WORD tokens based on spaces within their values.

int	new_tokens_count(t_data *pointer)
{
	int	i;
	int	j;
	int	k;

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

//count_characters counts the number of characters in a string until it encounters certain delimiter characters and returns the count.

int	count_characters(char const *s)
{
	int	length;

	length = 0;
	while (*s && *s != 32 && *s != '<' && *s != '>' && *s != '|'
		&& *s != '\'' && *s != 9 && *s != '\"')
	{
		s++;
		length++;
	}
	return (length);
}
