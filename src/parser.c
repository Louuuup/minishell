#include "../include/minishell.h"
#include "../lib/libft/libft.h"

//the counting_arguments function iterates through a range of tokens, counting the number of arguments in a command. It considers the position of the token in the command and the validity of the token type to determine whether it should be counted as an argument. The count is then returned as the result of the function.

int	counting_arguments(t_data *pointer, int index)
{
	int	count;
	
	count = 0;
	while (pointer->tokens[index].type != PIPE && pointer->count_token > index)
	{
		if ((index == 0
			|| check_if_redirection(pointer->tokens[index - 1].type))
			&& check_arguments(pointer->tokens[index].type))
			count++;
		index++;
	}
	return (count);
}

//the test_multiline function checks for the presence of certain redirection types (REDIRECT_MULTILINE and REDIRECT_IN) in a command and adjusts the no_space attribute accordingly for the first matching redirection. The loop iterates in reverse order through the redirections, and the function breaks out of the loop after processing the first matching redirection.

void	test_multiline(t_data *pointer, int index)
{
	int i;
	
	i = pointer->cmdt[index].num_redirections;
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

// cmdt_init serves as an initialization function for a command table entry, setting up various attributes and handling the initialization of command arguments, redirections, and multiline-related properties based on the given parameters.

int	cmdt_init(t_data *pointer, int i, int *index)
{
	pointer->cmdt[i].num_args = counting_arguments(pointer, *index);
	if (pointer->cmdt[i].num_args > 0)
	{
		pointer->cmdt[i].args = ft_calloc((pointer->cmdt[i].num_args + 1), sizeof(char *));
		if (!pointer->cmdt[i].args)
			return (error_out(pointer, "ft_calloc", 1));
	}
	else
		pointer->cmdt[i].args = 0;
	pointer->cmdt[i].last_multiline = 0;
	pointer->cmdt[i].file_out = -1;
	pointer->cmdt[i].file_in = -1;
	pointer->cmdt[i].out_fd = -1;
	pointer->cmdt[i].in_fd = -1;
	pointer->cmdt[i].pid = 0;
	pointer->cmdt[i].is_child_process = 0;
	pointer->cmdt[i].cmd = 0;
	if (redirections_fill(pointer, i, *index) == 1)
		return (1);
	test_multiline(pointer, i);
	*index = args_cmd_fill(pointer, i, *index - 1) + 1;
	if (*index == 0)
		return (1);
	return (0);
}

//the parser function is responsible for parsing the input data, merging words, counting pipes, allocating memory for command tables, and initializing each command table entry using the cmdt_init function. The function returns 0 on success and 1 on failure.

int	parser(t_data *pointer)
{
	int	j;
	int	i;
	
	i = 0;
	j = 0;
	if (words_merging(pointer) == 1)
		return (1);
	pointer->cmdt_count = count_pipes(pointer) + 1;
	pointer->cmdt = ft_calloc(pointer->cmdt_count, sizeof(t_tab_cmd));
	if (!pointer->cmdt)
		return (error_out(pointer, "ft_calloc", 1));
	while (j < pointer->cmdt_count)
	{
		if (cmdt_init(pointer, j, &i))
			return (1);
		j++;
	}
	return (0);
}