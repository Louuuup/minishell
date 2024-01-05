#include "../include/minishell.h"

//the copy_normalization function copies tokens from a temporary array to a new array while performing certain normalization checks, such as merging tokens with the previous one if necessary and marking specific tokens with no_space values.

int copy_normalization(t_token *new_tokens_array, int *i, int *j, char **tmp)
{
	int k;
	
	k = -1;
	if (new_tokens_array[*j].no_space == 1 && )*i > 0
	{
		*j = *j - 1;
		new_tokens_array[*j].value = ft_strjoin(new_tokens_array[*j].value, tmp[++k]);
		if (!new_tokens_array[*j].value)
			return (1);
		*j = *j + 1;
	}
	while (tmp[++k])
	{
		if (*j > 1 && k == 1
		&& check_if_redirection(new_tokens_array[*j - 2].type) == 0)
			new_tokens_array[*j - 2].no_space = 2;
		new_tokens_array[*j].value = ft_strdup(tmp[k]);
		if (!new_tokens_array[*j].value)
			return (1);
		*j = *j + 1;
	}
	return (0);
}

//the clean_double_pointer function is a memory cleanup function that frees the memory associated with a dynamically allocated array of strings and sets the double pointer to NULL to avoid potential dangling pointers

void	clean_double_pointer(char **pnt)
{
	int	i;

	i = -1;
	if (pnt)
	{
		while (pnt[++i])
		{
			free(pnt[i]);
			pnt[i] = NULL;
		}
		free(pnt);
		pnt = NULL;
	}
}

//the words_splitting function splits a token's value into words, copies and normalizes those words into a new array of tokens, and then cleans up the temporary array of words

int words_splitting(t_data *pntr, t_token *new_tkns, int *i, int *j)
{
	char	**tmp;

	tmp = ft_split(pntr->tokens[*i].value, ' ');
	if (!tmp)
		return (error_out(pntr, 1));
	if (!tmp[0])
	{
		clean_double_pointer(tmp);
		return (2);
	}
	if (copy_normalization(new_tkns, i, j, tmp) == 1)
	{
		clean_double_pointer(tmp);
		return (error_out(pntr, 1));
	}
	clean_double_pointer(tmp);
	return (0);
}

//the copy_concat_create function handles the copying and concatenation of values from the original array of tokens to a new array of tokens, taking into account the no_space flag for proper concatenation

int	copy_concat_create(t_data *pntr, t_token *tokens_new, int *j, int *i)
{
	if (tokens_new[*i].no_space == 1 && *j > 0)
	{
		*i = *i - 1;
		tokens_new[*i].value = ft_strjoin(tokens_new[*i].value,
			pntr->tokens[*j].value);
		if (!tokens_new[*i].value)
			return (error_out(pntr, 1));
	}
	else
	{
		tokens_new[*i].value = ft_strdup(pntr->tokens[*j].value);
		if (!tokens_new[*i].value)
			return (error_out(pntr, 1));
	}
	*i = *i + 1;
	return (0);
}

//the token_copy function copies tokens from the original array to the new array, handling different token types appropriately and considering the no_space flag. If the token is of type WORD, it may call words_splitting to handle potential splitting of the token's value.

int	token_copy(t_data *pointer, t_token *tokens_new, int *i, int *j)
{
	int	buffer;

	tokens_new[*j].type = pointer->tokens[*i].type;
	if (check_arguments(pointer->tokens[*i].type) == 1)
	{
		if (pointer->tokens[*i].type == WORD)
		{
			buffer = words_splitting(pointer, tokens_new, i, j);
			if (buffer == 2 || buffer == 1)
				return (buffer % 2);
		}
		else
			if (copy_concat_create(pointer, tokens_new, i, j) == 1)
				return (1);
		tokens_new[*j].no_space = pointer->tokens[*i].no_space;
	}
	else
		*j = *j + 1;
	return (0);
}