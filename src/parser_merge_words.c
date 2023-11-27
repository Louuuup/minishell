#include "../include/minishell.h"

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
		function_to_free_double_pointer_memory(tmp);
		return (2);
	}
	if (function_proper_copy_from_tmp_to_t_token_array(new_tkns, i, j, tmp) == 1)
	{
		function_to_free_double_pointer_memory(tmp);
		return (error_out(pntr, 1));
	}
	function_to_free_double_pointer_memory(tmp);
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
			if (function_copy_not_word(pointer, tokens_new, i, j) == 1)
				return (1);
		tokens_new[*j].no_space = pointer->tokens[*i].no_space;
	}
	else
		*j++;
	return (0);
}