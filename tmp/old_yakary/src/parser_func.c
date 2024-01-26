#include "../include/minishell.h"

//the redirections_count function counts the number of redirections in a command by iterating through the tokens and incrementing the count for each token that is not a redirection
int	redirections_count(t_data *pnt, int i)
{
	int cnt;

	cnt = 0;
	while (pnt->tokens[i].type != PIPE && pnt->count_token > i)
	{
		if (check_if_redirection(pnt->tokens[i].type) == 0)
			cnt++;
		i++;
	}
	return (cnt);
}

//the redirections_fill function fills in information about redirections for a specific command in the project. It updates the command table with the number of redirections and details about each redirection
int	redirections_fill(t_data *pnt, int j, int i)
{
	int cnt;

	cnt = redirections_count(pnt, i);
	pnt->cmdt[j].redirections = NULL;
	pnt->cmdt[j].num_redirections = cnt;
	if (cnt <= 0)
		return (0);
	pnt->cmdt[i].redirections = ft_calloc(cnt, sizeof(t_token));
	if (!pnt->cmdt[j].redirections)
		return (error_out(pnt, "ft_calloc", 1));
	cnt = 0;
	while (pnt->tokens[i].type != PIPE && pnt->count_token > i)
	{
		if (check_if_redirection(pnt->tokens[i].type) == 0)
		{
			pnt->cmdt[j].redirections[cnt].type = pnt->tokens[i].type;
			pnt->cmdt[j].redirections[cnt].no_space = pnt->tokens[i].no_space;
			pnt->cmdt[j].redirections[cnt].value = ft_strdup(pnt->tokens[1 + i++].value);
			if (!pnt->cmdt[j].redirections[cnt++].value)
				return (error_out(pnt, "ft_strdup", 1));
		}
		i++;
	}
	return (0);
}

//the args_cmd_fill function fills in the arguments and the command itself for a specific command in the project. It iterates through the tokens, identifies arguments, and populates the corresponding fields in the command table
// int	args_cmd_fill(t_data *pnt, int j, int i, int k)
// {
// 	int tmp_num_args;

// 	tmp_num_args = pnt->cmdt[j].num_args;
// 	while (++i < pnt->count_token && pnt->tokens[i].type != PIPE)
// 	{
// 		if (check_arguments(pnt->tokens[i].type)
// 			&& (i == 0 || check_if_redirection(pnt->tokens[i - 1].type)))
// 		{
// 			if (pnt->cmdt[j].num_args-- > 0 && pnt->tokens[i].type == WORD
// 				&& pnt->tokens[i].value[0] == '\0')
// 					continue ;
// 			if (pnt->cmdt[j].cmd == NULL)
// 			{
// 				pnt->cmdt[j].cmd = ft_strdup(pnt->tokens[i].value);
// 				if (!pnt->cmdt[j].cmd)
// 					return (error_out(pnt, "ft_strdup", 1) - 2);
// 			}
// 			pnt->cmdt[j].args[k++] = ft_strdup(pnt->tokens[i].value);
// 			if (!pnt->cmdt[j].args[k - 1])
// 				return (error_out(pnt, "ft_strdup", 1) - 2);
// 		}
// 	}
// 	if (pnt->cmdt[j].cmd != NULL)
// 		pnt->cmdt[j].args[k] = NULL;
// 	return (i);
// }
//new functin to replace the above, testing.
int	args_cmd_fill(t_data *pnt, int j, int i, int k)
{
	int tmp_num_args;

	tmp_num_args = pnt->cmdt[j].num_args;
    while (++i < pnt->count_token && pnt->tokens[i].type != PIPE)
    {
        if (check_arguments(pnt->tokens[i].type)
            && (i == 0 || check_if_redirection(pnt->tokens[i - 1].type)))
        {
            if (!(pnt->cmdt[j].num_args-- > 0 && pnt->tokens[i].type == WORD
                && pnt->tokens[i].value[0] == '\0'))
            {
                if (handle_strdup(pnt, j, k++, pnt->tokens[i].value) < 0)
                    return -2;
            }
        }
    }
    if (pnt->cmdt[j].cmd) pnt->cmdt[j].args[k] = NULL;
	pnt->cmdt[j].num_args = tmp_num_args;
    return (i);
}

//the clean_tokens function is used to free the memory allocated for the values of tokens in the array and then free the memory allocated for the tokens array itself. After cleanup, it sets the pointers to NULL to avoid potential issues with dangling pointers

int	clean_tokens(t_token *tokens, int max, t_data *pnt)
{
	while (pnt->count_token > ++max)
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

//the words_merging function performs the merging of adjacent WORD tokens and updates the count_token and tokens accordingly. It also deallocates the memory used by the original tokens array

int	words_merging(t_data *pnt)
{
	t_token	*tokens_new;
	int		k;
	int		j;
	int		i;

	k = -1;
	j = 0;
	i = 0;
	tokens_new = ft_calloc(new_tokens_count(pnt) + 1, sizeof(t_token));
	if (!tokens_new)
		return (error_out(pnt, "ft_calloc", 1));
	while (pnt->count_token > i)
	{
		if (token_copy(pnt, tokens_new, &i, &j) == 1)
			return (clean_tokens(tokens_new, -1, pnt));
		i++;
	}
	while (pnt->count_token > ++k)
		if (pnt->tokens[k].value)
			free(pnt->tokens[k].value);
	free(pnt->tokens);
	pnt->tokens = tokens_new;
	pnt->count_token = j;
	return (0);
}
