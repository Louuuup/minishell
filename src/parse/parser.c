#include "../../include/minishell.h"
#include "../../lib/libft/libft.h"

// we need to find the quantity of arguments of the data structure till the pipe sign
// 'pointer' is a pointer to a structure called t_data with information about the tokens
// The index is for counting the arguments in the data->tokens array

int	counting_arguments(t_data *pointer, int index)
{
	int count = 0;

	while (index < pointer->count_token && pointer->tokens[index].type != PIPE)
	{
		if (check_arguments(pointer->tokens[index].type) && (index == 0
			|| check_if_redirection(pointer->tokens[index - 1].type)))
			count++;
		index++;
	}
	return (count);
}

// the function test if the last redirection was multi-line or input redirection

void	test_multiline(t_data *pointer, int index)
{
	int i = pointer->cmdt[index].num_redirections;
	while(i--)
	{
		if (pointer->cmdt[index].redirections[i].type == REDIRECT_MULTILINE
			|| pointer->cmdt[index].redirections[i].type == REDIRECT_IN)
		{
			if (pointer->cmdt[index].redirections[i].type == REDIRECT_MULTILINE)
				pointer->cmdt[index].redirections[i].no_space = 3;
			break;
		}
	}
}

// the function fills the fields of t_tab_cmd in t_data struct

int	cmdt_init(t_data *pointer, int i, int *index)
{
	pointer->cmdt[i].num_args = counting_arguments(pointer, *index);
	if (pointer->cmdt[i].num_args > 0)
	{
		pointer->cmdt[i].args = ft_calloc((pointer->cmdt[i].num_args + 1), sizeof(char *));
		if (!pointer->cmdt[i].args)
			return (error_out(pointer, "ft_calloc error"));
	}
	else
		pointer->cmdt[i].args = 0;
	pointer->cmdt[i].cmd = 0;
	pointer->cmdt[i].is_child_process = 0;
	pointer->cmdt[i].pid = 0;
	pointer->cmdt[i].fd_in = -1;
	pointer->cmdt[i].fd_out = -1;
	pointer->cmdt[i].in_file = -1;
	pointer->cmdt[i].out_file = -1;
	pointer->cmdt[i].last_multiline = 0;
	if (1)// redirection logic
		return (1);
	last_multiline(pointer, i);
	//*index = fill command arguments
	if (*index == 0)
		return (1);
	return (0);
}