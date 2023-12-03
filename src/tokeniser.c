#include "../include/minishell.h"

//this function check the syntax of redirection tokens of the data structure

int	check_syntax_redirection(t_data *pntr, int i)
{
	if ((check_if_redirection(pntr->tokens[i + 1].type) == 0)
		&& ((pntr->tokens[i].type == REDIRECT_OUT)
		|| (pntr->tokens[i].type == REDIRECT_IN)
		|| (pntr->tokens[i].type == REDIRECT_APPEND
		|| pntr->tokens[i].type == REDIRECT_MULTILINE)))
		return (function_error_in_syntax(pntr->tokens[i + 1].type, pntr), 1);
	return (0);
}

//checks the syntax of the data structure and returns true if it finds syntax error
//in other case it returns false

int	syntax_checking(t_data *pntr)
{
	int	i;

	i = 0;
	while (pntr->count_token > i)
	{
		if ((pntr->count_token - 1 == i && pntr->tokens[i].type == PIPE)
			|| (i == 0 && pntr->tokens[i].type == PIPE)
			|| (pntr->tokens[i].type == PIPE && pntr->tokens[i + 1].type == PIPE)
			|| (pntr->tokens[i].type == PIPE
				&& (check_if_redirection(pntr->tokens[i - 1].type) == 0)))
			return (error_in_syntax(pntr->tokens[i].type, pntr), 1);
		else if (check_if_redirection(pntr->tokens[i].type) == 0
			&& pntr->count_token - 1 == i)
			return (error_in_syntax(0, pntr), 1);
		else if (check_syntax_redirection(pntr, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

//'tokeniser' breaks the input by spaces, quotes, special characters;
//allocate memory for these tokens;
//also it checks syntax. A token has 3 variables:
//TYPE (which one?),
//VALUE (is there speacial characters?),
//NO_SPACE (followed by token to be concatenated?)

int tokeniser(t_data *pntr)
{
	int	i;

	i = 0;
	pntr->tokens = ft_calloc(pntr->max_token, sizeof(t_token));
	if (!pntr->tokens)
		return (error_out(pntr, 1));
	while (pntr->input[i])
	{
		if (function_to_fill_with_tokens(pntr, &i, 0) == 1)
			return (1);
		i++;
	}
	return (syntax_checking(pntr));
}
