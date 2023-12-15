#include "minishell.h"

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

void	exec_main(t_data *data)
{
	if (!data->cmdt)
		return ;
	if (data->cmdt->cmd)
		printf("cmd1 = %s\n", data->cmdt->cmd);
	
}
