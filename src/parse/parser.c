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
}