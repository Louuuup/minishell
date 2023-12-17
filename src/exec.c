#include "minishell.h"

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

void	exec_main(t_data *data)
{
	// t_cmd	*tmp;

	// if (!data->cmdt)
	// 	return ;
	// if (data->cmdt->cmd)
	// 	printf("cmd1 = %s\n", data->cmdt->cmd);

	// tmp = data->cmdt->cmd;
	// while(tmp)
	// {
	// 	// if (tmp->)
	// 	tmp = tmp->next;
	// }

	int	i;
	int	pip[2];

	i = 0;
	//put field in data struct holding state of previous fd to -1
	while(i < data->cmdt_count)
	{
		if (pipe(pip) == -1)
			return ((void)error_out(data, 1));
		//manage the redirection of input and output for a command in a pipeline
		//then
		//sets the input and output file descriptors for a command table based on the specified input & output files or the previous files descriptors
		//then
		//if (check the command for builtins)
			//execute the builtin command
		//else
		i++;
	}
}
