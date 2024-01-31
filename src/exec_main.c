#include "minishell.h"

void	exec_main(t_data *data)
{
	t_cmd	*cmd;
	int		pid[2];

	cmd = data->cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
		if (cmd->index == 0 && cmd->infile)
			cmd->fd_in = open(cmd->infile, O_RDONLY);
	}
}
