#include "../include/minishell.h"

//is designed to check the syntax of redirections in the command tokens. It specifically checks whether the next token after a redirection operator is valid and prints a syntax error message if it's not.

int	check_syntax_redirection(t_data *pnt, int i)
{
	// if ((check_if_redirection(pnt->tokens[i + 1].type) == 0)
	// 	&& ((pnt->tokens[i].type == REDIRECT_OUT)
	// 	|| (pnt->tokens[i].type == REDIRECT_IN)
	// 	|| (pnt->tokens[i].type == REDIRECT_APPEND
	// 	|| pnt->tokens[i].type == REDIRECT_MULTILINE)))
	// 	return (error_in_syntax(pnt->tokens[i + 1].type, pnt), 1);
	// return (0);
	if (pnt->tokens[i].type == REDIRECT_APPEND
		&& (check_if_redirection(pnt->tokens[i + 1].type) == 0))
		return (error_in_syntax(pnt->tokens[i + 1].type, pnt), 1);
	else if (pnt->tokens[i].type == REDIRECT_MULTILINE
		&& (check_if_redirection(pnt->tokens[i + 1].type) == 0))
		return (error_in_syntax(pnt->tokens[i + 1].type, pnt), 1);
	else if (pnt->tokens[i].type == REDIRECT_IN
		&& (check_if_redirection(pnt->tokens[i + 1].type) == 0))
		return (error_in_syntax(pnt->tokens[i + 1].type, pnt), 1);
	else if (pnt->tokens[i].type == REDIRECT_OUT
		&& (check_if_redirection(pnt->tokens[i + 1].type) == 0))
		return (error_in_syntax(pnt->tokens[i + 1].type, pnt), 1);
	return (0);
}

//this function performs syntax checking on command tokens, specifically checking for errors related to pipes and redirections. If it encounters a syntax error, it calls error_in_syntax and returns 1; otherwise, it returns 0.

int	syntax_checking(t_data *pnt)
{
	int	i;

	i = -1;
	while (pnt->count_token > ++i)
	{
		if (pnt->count_token - 1 == i && pnt->tokens[i].type == PIPE)
			return (error_in_syntax(pnt->tokens[i].type, pnt), 1);
		else if (i == 0 && pnt->tokens[i].type == PIPE)
			return (error_in_syntax(pnt->tokens[i].type, pnt), 1);
		else if (pnt->tokens[i].type == PIPE && pnt->tokens[i + 1].type == PIPE)
			return (error_in_syntax(pnt->tokens[i].type, pnt), 1);
		else if (pnt->tokens[i].type == PIPE
				&& (check_if_redirection(pnt->tokens[i - 1].type) == 0))
			return (error_in_syntax(pnt->tokens[i].type, pnt), 1);
		else if (check_if_redirection(pnt->tokens[i].type) == 0
			&& pnt->count_token - 1 == i)
			return (error_in_syntax(0, pnt), 1);
		else if (check_syntax_redirection(pnt, i) == 1)
			return (1);
	}
	return (0);
}

//the fill_redirection function is used to identify and set the appropriate redirection type in the pnt structure based on the provided string (str). It updates the token type according to the encountered redirection symbol ('>' or '<') and, if applicable, the presence of consecutive symbols. The function returns the total number of updates made to the pnt structure (initially set to 1).

int	fill_redirection(t_data *pnt, char const *str)
{
	int result;

	result = 1;
	pnt->count_token++;
	if ('>' == *str)
	{
		pnt->tokens[pnt->count_token - 1].type = REDIRECT_OUT;
		if (result++ && '>' == *(str + 1))
			pnt->tokens[pnt->count_token - 1].type = REDIRECT_APPEND;
	}
	else if ('<' == *str)
	{
		pnt->tokens[pnt->count_token - 1].type = REDIRECT_IN;
		if (result++ && '<' == *(str + 1))
			pnt->tokens[pnt->count_token - 1].type = REDIRECT_MULTILINE;
	}
	return (result);
}

//the func parses the input & fills the array of tokens with the right types

int	filling_with_tokens(t_data *pnt, int *i, int j)
{
	if (pnt->count_token == pnt->max_token)
		if (reallocate_tokens_if_max(pnt, pnt->max_token) == 1)
			return (1);
	if (pnt->input[*i] == '|')
		pnt->tokens[++pnt->count_token - 1].type = PIPE;
	else if (pnt->input[*i] == '>' || pnt->input[*i] == '<')
		*i += fill_redirection(pnt, &pnt->input[*i]) - 1;
	else if (pnt->input[*i] == '\"' || pnt->input[*i] == '\'')
	{
		j = filling_quotes(pnt, &pnt->input[*i], pnt->input[*i]) - 1;
		if (j == -2)
			return (1);
		if (j == -1)
			return (error_in_syntax(pnt->input[*i], pnt), 1);
		*i += j;
	}
	else if (pnt->input[*i] != 9 && pnt->input[*i] != 32)
	{
		j = word_filling(pnt, &pnt->input[*i]) - 1;
		if (j == -1)
			return (error_out(pnt, "ft_calloc", 1));
		*i += j;
	}
	return (0);
}

//the tokener function is responsible for tokenizing the input provided to the shell. It allocates memory for tokens, iterates through the input, fills token information using filling_with_tokens, and performs syntax checking on the generated tokens. If any error occurs during these processes, it returns 1; otherwise, it returns the result of the syntax checking. A token has 3 variables:
//TYPE (which one?),
//VALUE (is there special characters?),
//NO_SPACE (followed by token to be concatenated?)

int tokener(t_data *pnt)
{
	int	i;

	i = -1;
	pnt->tokens = ft_calloc(pnt->max_token, sizeof(t_token));
	if (!pnt->tokens)
		return (error_out(pnt, "ft_calloc", 1));
	while (pnt->input[++i])
		if (filling_with_tokens(pnt, &i, 0) == 1)
			return (1);
	return (syntax_checking(pnt));
}
