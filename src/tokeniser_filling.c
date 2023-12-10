#include "../include/minishell.h"

//the func clean the memory of an array for tokens & fill it with 0s

int clean_token_array(t_token *array_tokens, int max_number_token, t_data *pntr)
{
	while (++max_number_token < pntr->count_token)
	{
		if (array_tokens[max_number_token].value)
		{
			free(array_tokens[max_number_token].value);
			array_tokens[max_number_token].value = NULL;
		}
	}
	free(array_tokens);
	array_tokens = NULL;
	return (1);
}

//the func evaluate the length of a string skipping the delimiters

int	count_characters(char const *s)
{
	int	length;

	length = 0;
	while (*s != ' ' &&  *s != '<' && *s != '>' && *s != '|' && *s != '\'' && *s != '\t' && *s!= '\"' && *s)
	{
		s++;
		length++;
	}
	return (length);
}

//the func puts characters in a token. The chars are from a string input. The func goes
//through till it meets a delimiter. Then it assigns the type of the token as WORD

int word_filling(t_data *pntr, char const *str)
{
	int	i;

	i = 0;
	pntr->tokens[++pntr->count_token - 1].value = ft_calloc(count_characters(str) + 1, sizeof(char));

}

//the func reallocate memory if there's no more space for tokens

int reallocate_tokens_if_max(t_data *pntr, int max_token)
{
	t_token *new_tokens_array;

	new_tokens_array = ft_calloc(max_token * 2, sizeof(t_token));
	if (!new_tokens_array)
		return (error_out(pntr, 1));
	while (--max_token >= 0)
	{
		new_tokens_array[max_token].type = pntr->tokens[max_token].type;
		if (pntr->tokens[max_token].value)
		{
			new_tokens_array[max_token].value = ft_strdup(pntr->tokens[max_token].value);
			if (!new_tokens_array[max_token].value)
				return (clean_token_array(new_tokens_array, max_token, pntr));
		}
		new_tokens_array[max_token].no_space = pntr->tokens[max_token].no_space;
		free(pntr->tokens[max_token].value);
	}
	free(pntr->tokens);
	pntr->tokens = new_tokens_array;
	pntr->max_token *= 2;
	return (0);
}