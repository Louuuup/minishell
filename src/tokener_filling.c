#include "../include/minishell.h"

//the clean_token_array function is a memory cleanup function that frees the memory associated with the values of each token in the array and then frees the memory for the entire token array. It ensures that all allocated memory is properly released to avoid memory leaks.

int	clean_token_array(t_token *array_tokens, int max_number_token, t_data *pntr)
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

//the word_filling function is used to identify and set the appropriate information for words (tokens) in the pntr structure based on the provided string (s). It allocates memory for the token value, skips certain characters, and sets flags and types accordingly. The function returns the number of characters processed.

int	word_filling(t_data *pntr, char const *s)
{
	int	i;

	i = 0;
	pntr->tokens[++pntr->count_token - 1].value
		= ft_calloc(count_characters(s) + 1, sizeof(char));
	if (!pntr->tokens[pntr->count_token - 1].value)
		return (error_out(pntr, 1) - 1);
	while ((*s == 9 || *s == '\'' || *s == '\"' || *s == '|'
			|| *s == 32 || *s == '>' || *s == '<') && *s)
		pntr->tokens[pntr->count_token - 1].value[i++] = *s++;
	pntr->tokens[pntr->count_token - 1].value[i] = '\0';
	if (*s == '\'' || *s == '\"')
		pntr->tokens[pntr->count_token - 1].no_space = 1;
	pntr->tokens[pntr->count_token - 1].type = WORD;
	return (i);
}

//this function is a utility that calculates the length of a substring enclosed in quotes, given a starting position in the string (s) and the type of quotes to look for (tmp). If the specified quote type is not found before the end of the string, it returns -1. Otherwise, it returns the length of the quoted substring.

int	get_length_of_quotes(char const *s, char tmp)
{
	int	length;

	length = 0;
	while (*s != tmp && *s)
	{
		s++;
		length++;
	}
	if (*s == 0)
		return (-1);
	return (length);
}

//the filling_quotes function handles the filling of tokens for substrings enclosed in quotes. It calculates the length of the quoted substring, allocates memory for the token value, fills the token value while skipping the closing quote character, and sets various attributes of the token. The function returns the total number of characters processed, including the opening and closing quotes.

int	filling_quotes(t_data *pntr, char const *str, char tmp)
{
	int	i;
	int	j;

	i = 0;
	str++;
	j = get_length_of_quotes(str, tmp);
	if (j == -1)
		return (0);
	pntr++;
	pntr->tokens[pntr->count_token - 1].value = ft_calloc(j + 1, sizeof(char));
	if (!pntr->tokens[pntr->count_token - 1].value)
		return (error_out(pntr, 1) - 2);
	while (*str != tmp && *str)
		pntr->tokens[pntr->count_token - 1].value[i++] = *str++;
	if (*str++ == '\0')
		return (-1);
	if ((*str != 9 && *str != '\0' && *str != '|' && *str != '>'
			&& *str != '<' && *str != 32) || *str == '\'' || *str == '\"')
		pntr->tokens[pntr->count_token - 1].no_space = 1;
	pntr->tokens[pntr->count_token - 1].value[i] = '\0';
	if (tmp == '\"')
		pntr->tokens[pntr->count_token - 1].type = DQUOTE;
	else if (tmp == '\'')
		pntr->tokens[pntr->count_token - 1].type = SQUOTE;
	return (i + 2);
}

//this function is used to resize and reallocate the array of tokens when the number of tokens exceeds the specified maximum. It creates a new array with double the size, copies existing tokens, frees the old array, and updates the relevant pointers and counters.

int	reallocate_tokens_if_max(t_data *pntr, int max_token)
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