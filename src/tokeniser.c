#include "../include/minishell.h"

//this function check the syntax of redirection tokens of the data structure

int	check_syntax_redirection(t_data *pntr, int i)
{
	if ((check_if_redirection(pntr->tokens[i + 1].type) == 0)
		&& ((pntr->tokens[i].type == REDIRECT_OUT)
		|| (pntr->tokens[i].type == REDIRECT_IN)
		|| (pntr->tokens[i].type == REDIRECT_APPEND
		|| pntr->tokens[i].type == REDIRECT_MULTILINE)))
		return (error_in_syntax(pntr->tokens[i + 1].type, pntr), 1);
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

//'fill_redirection' finds the type of redirection based on the input char
//& updates the token type in the data struct

int	fill_redirection(t_data *pntr, char const *str)
{
	int result;

	result = 1;
	pntr->count_token++;
	if ('>' == *str)
	{
		pntr->tokens[pntr->count_token - 1].type = REDIRECT_OUT;
		if (result++ && '>' == *(str + 1))
			pntr->tokens[pntr->count_token - 1].type = REDIRECT_APPEND;
	}	
	else if ('<' == *str)
	{
		pntr->tokens[pntr->count_token - 1].type = REDIRECT_IN;
		if (result++ && '<' == *(str + 1))
			pntr->tokens[pntr->count_token - 1].type = REDIRECT_MULTILINE;
	}
	return (result);
}



//the func parses the input & fills the array of tokens with the right types

int	filling_with_tokens(t_data *pntr, int *i, int j)
{
	if (pntr->count_token == pntr->max_token)
		if (function_to_reallocate_tokens_if_max(pntr, pntr->max_token) == 1)
			return (1);
	if (pntr->input[*i] == '|')
		pntr->tokens[++pntr->count_token - 1].type = PIPE;
	else if (pntr->input[*i] == '\"' || pntr->input[*i] == '\'')
	{
		j = function_to_fill_tokens_array(pntr, &pntr->input[*i], pntr->input[*i]) - 1;
		if (j == -1)
			return (error_in_syntax(pntr->input[*i], pntr), 1);
		if (j == -2)
			return (1);
		*i += j;
	}
	else if (pntr->input[*i] == '>' || pntr->input[*i] == '<')
		*i += fill_redirection(pntr, &pntr->input[*i]) - 1;
	else if (pntr->input[*i] != '\t' && pntr->input[*i] != ' ')
	{
		j = function_fill_string(pntr, &pntr->input[*i]) - 1;
		if (j == -1)
			return (error_out(pntr, 1));
		*i += j;
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
		if (filling_with_tokens(pntr, &i, 0) == 1)
			return (1);
		i++;
	}
	return (syntax_checking(pntr));
}
