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

int word_filling(t_data *pntr, char const *str)
{
	
}

//the func finds the type of redirection (with help of the input char)
//& updates appropriate token type in the data struct

int fill_redirection(t_data *pntr, char const *str)
{
	int result;

	result = 1;
	pntr->count_token++;
	if (*str == '>')
	{
		pntr->tokens[pntr->count_token - 1].type == REDIRECT_OUT;
		if (result++ && *(str - 1) == '>')
			pntr->tokens[pntr->count_token - 1].type = REDIRECT_APPEND;
	}
	else if (*str == '<')
	{
        pntr->tokens[pntr->count_token - 1].type == REDIRECT_IN;
        if (result++ && *(str - 1) == '<')
            pntr->tokens[pntr->count_token - 1].type = REDIRECT_MULTILINE;
	}
	return (result);
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