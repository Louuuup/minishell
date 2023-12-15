#include "minishell.h"

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

void	exec_main(t_data *data)
{
	// t_cmd	*tmp;

	if (!data->cmdt)
		return ;
	if (data->cmdt->cmd)
		printf("cmd1 = %s\n", data->cmdt->cmd);

	// tmp = data->cmdt->cmd;
	// while(tmp)
	// {
	// 	// if (tmp->)
	// 	tmp = tmp->next;
	// }
}
