#include "../include/minishell.h"

//'copy_normalization' copies what we have in 'temp' array to 'new_tokens' array
//inserting spaces and redirections

int copy_normalization(t_token *new_tokens_array, int *i, int *j, char **tmp)
{
	int k;
	
	k = -1;
	if (new_tokens_array[*j].no_space == 1 && *i > 0)
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

//'clean_double_pointer' clean memory for the double pointer and set it to NULL

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

//'split_words' breaks a string into separated words and then put them to
//a new array of tokens

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

//'copy_concat_create' function makes a copy of a token's value to a new array of tokens.
//It could be concatenation of the token's value we had before or creating a new string

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

//token_copy function takes copies of a token from the t_data struct to
//the array of new tokens. At the same time it handles different types of
//tokens and splits words

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