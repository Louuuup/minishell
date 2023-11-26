#include "../include/minishell.h"

// "redirection_fill" fills the array of redirections
//in the data structure with information from the
// token array

int	redirections_fill(t_data *pointer, int i, int j)
{
	int cnt;

	cnt = redirections_cnt(pointer, j);
	pointer->cmdt[i].redirections = NULL;
	pointer->cmdt[i].num_redirections = cnt;
	if (cnt <= 0)
		return (0);
	pointer->cmdt[i].redirections = ft_calloc(cnt, sizeof(t_token));
	if (!pointer->cmdt[i].redirections)
		return (error_out(pointer, 1));
	cnt = 0;
	while (pointer->count_token > j && pointer->tokens[j].type != PIPE)
	{
		if (check_if_redirection(pointer->tokens[j].type) == 0)
		{
			pointer->cmdt[i].redirections[cnt].type = pointer->tokens[j].type;
			pointer->cmdt[i].redirections[cnt].no_space = pointer->tokens[j].no_space;
			pointer->cmdt[i].redirections[cnt].value = ft_strdup(pointer->tokens[1 + i++].value);
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
	int k = 0;
	while (pointer->tokens[j].type != PIPE && pointer->count_token > ++j)
	{
		if (check_arguments(pointer->tokens[j].type)
			&& (check_if_redirection(pointer->tokens[j - 1].type)) || i == 0)
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