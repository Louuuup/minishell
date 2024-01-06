#include "../include/minishell.h"

//is designed to check the syntax of redirections in the command tokens. It specifically checks whether the next token after a redirection operator is valid and prints a syntax error message if it's not.

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

//this function performs syntax checking on command tokens, specifically checking for errors related to pipes and redirections. If it encounters a syntax error, it calls error_in_syntax and returns 1; otherwise, it returns 0.

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

//the fill_redirection function is used to identify and set the appropriate redirection type in the pntr structure based on the provided string (str). It updates the token type according to the encountered redirection symbol ('>' or '<') and, if applicable, the presence of consecutive symbols. The function returns the total number of updates made to the pntr structure (initially set to 1).

int	fill_redirection(t_data *pntr, char const *str)
{
	int result;

	pntr->count_token += 1;
	result = 1;
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
		if (reallocate_tokens_if_max(pntr, pntr->max_token) == 1)
			return (1);
	if (pntr->input[*i] == '|')
		pntr->tokens[++pntr->count_token - 1].type = PIPE;
	else if (pntr->input[*i] == '>' || pntr->input[*i] == '<')
		*i += fill_redirection(pntr, &pntr->input[*i]) - 1;
	else if (pntr->input[*i] != 9 && pntr->input[*i] != 32)
	{
		j = word_filling(pntr, &pntr->input[*i]) - 1;
		if (j == -1)
			return (error_out(pntr, "ft_calloc", 1));
		*i += j;
	}
	else if (pntr->input[*i] == '\"' || pntr->input[*i] == '\'')
	{
		j = filling_quotes(pntr, &pntr->input[*i], pntr->input[*i]) - 1;
		if (j == -1)
			return (error_in_syntax(pntr->input[*i], pntr), 1);
		if (j == -2)
			return (1);
		*i += j;
	}
	return (0);
}

//the tokener function is responsible for tokenizing the input provided to the shell. It allocates memory for tokens, iterates through the input, fills token information using filling_with_tokens, and performs syntax checking on the generated tokens. If any error occurs during these processes, it returns 1; otherwise, it returns the result of the syntax checking. A token has 3 variables:
//TYPE (which one?),
//VALUE (is there special characters?),
//NO_SPACE (followed by token to be concatenated?)

int tokener(t_data *pntr)
{
	int	i;

	i = 0;
	pntr->tokens = ft_calloc(pntr->max_token, sizeof(t_token));
	if (!pntr->tokens)
		return (error_out(pntr, "ft_calloc", 1));
	while (pntr->input && pntr->input[i])
	{
		if (filling_with_tokens(pntr, &i, 0) == 1)
			return (1);
		i++;
	}
	return (syntax_checking(pntr));
}
