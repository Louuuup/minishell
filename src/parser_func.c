#include "../include/minishell.h"

//'redirections_count' counts the # of redirecting tokens in a
//received array of tokens

int	redirections_count(t_data *pointer, int i)
{
	int cnt;

	cnt = 0;
	while (pointer->tokens[i].type != PIPE && pointer->count_token > i)
	{
		if (check_if_redirection(pointer->tokens[i].type) == 0)
			cnt++;
		i++;
	}
	return (cnt);
}

// "redirection_fill" fills the array of redirections
//in the data structure with information from the
// token array

int	redirections_fill(t_data *pointer, int i, int j)
{
	int cnt;

	cnt = redirections_count(pointer, j);
	if (cnt <= 0)
		return (0);
	pointer->cmdt[i].num_redirections = cnt;
	pointer->cmdt[i].redirections = NULL;
	pointer->cmdt[i].redirections = ft_calloc(cnt, sizeof(t_token));
	if (!pointer->cmdt[i].redirections)
		return (error_out(pointer, 1));
	cnt = 0;
	while (pointer->tokens[j].type != PIPE && pointer->count_token > j)
	{
		if (check_if_redirection(pointer->tokens[j].type) == 0)
		{
			pointer->cmdt[i].redirections[cnt].value = ft_strdup(pointer->tokens[1 + j++].value);
			pointer->cmdt[i].redirections[cnt].no_space = pointer->tokens[j].no_space;
			pointer->cmdt[i].redirections[cnt].type = pointer->tokens[j].type;
			if (!pointer->cmdt[i].redirections[cnt++].value)
				return (error_out(pointer, 1));
		}
		j++;
	}
	return (0);
}

//"args_cmds_fill" fills arrays of arguments & commands in the data structure
//taking them from the tokens

int	args_cmd_fill(t_data *pointer, int i, int j)
{
	int k;
	
	k = 0;
	while (pointer->tokens[j].type != PIPE && pointer->count_token > ++j)
	{
		if (check_arguments(pointer->tokens[j].type)
			&& (check_if_redirection(pointer->tokens[j - 1].type) || i == 0))
		{
			if (pointer->cmdt[i].cmd == NULL)
			{
				pointer->cmdt[i].cmd = ft_strdup(pointer->tokens[j].value);
				if (!pointer->cmdt[i].cmd)
					return (error_out(pointer, 1) - 2);
			}
			if (pointer->cmdt[i].num_args-- > 0 && pointer->tokens[j].type == WORD
				&& pointer->tokens[j].value[0] == '\0')
					continue ;			
			pointer->cmdt[i].args[k++] = ft_strdup(pointer->tokens[j].value);
			if (!pointer->cmdt[i].args[k - 1])
				return (error_out(pointer, 1) - 2);
		}
	}
	if (pointer->cmdt[i].cmd != NULL)
		pointer->cmdt[i].args[k] = NULL;
	return (i);
}

//'clean_tokens' clean the memory taken for an array of tokens and put zeros in it

int	clean_tokens(t_token *tokens, int max, t_data *pointer)
{
	while (pointer->count_token > ++max)
	{
		if (tokens[max].value)
		{
			free(tokens[max].value);
			tokens[max].value = NULL;
		}
	}
	free(tokens);
	tokens = NULL;
	return (1);
}

//'words_merging' func merge sequent token of the same type into a united token

int	words_merging(t_data *pointer)
{
	int		k;
	int		j;
	int		i;
	t_token	*tokens_new;

	k = -1;
	j = 0;
	i = 0;
	tokens_new = ft_calloc(new_tokens_count(pointer) + 1, sizeof(t_token));
	if (!tokens_new)
		return (error_out(pointer, 1));
	while (pointer->count_token > i)
	{
		if (token_copy(pointer, tokens_new, &i, &j) == 1)	
			return (clean_tokens(tokens_new, -1, pointer));
		i++;
	}
	while (pointer->count_token > ++k)
		if (pointer->tokens[k].value)
			free(pointer->tokens[k].value);
	free(pointer->tokens);
	pointer->count_token = j;
	pointer->tokens = tokens_new;
	return (0);
}