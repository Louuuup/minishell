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

void	test_multiline(t_data *data, int index)
{
	int i = data->cmdt[index].num_redirections;
	while(i--)
	{
		if (data->cmdt[index].redirections[i].type == REDIRECT_MULTILINE
			|| data->cmdt[index].redirections[i].type == REDIRECT_IN)
		{
			if (data->cmdt[index].redirections[i].type == REDIRECT_MULTILINE)
				data->cmdt[index].redirections[i].no_space = 3;
			break;
		}
	}
}