#include "minishell.h"

void	exec_main(t_data *data)
{
	t_cmd	*cmd;
	// int		pid[2];

	cmd = data->cmd;
	if (!cmd)
		return ;
	while (cmd->next)
	{
		if (ft_pipe(cmd))
			error_str("pipe error\n");
		cmd = cmd->next;
	}
	cmd = data->cmd;
	if (cmd->infile && cmd->in_flag == REDIR_INPUT)
		cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, O_RDONLY);

}


void redirect_check(t_cmd *cmd)
{
	if (cmd->infile && cmd->in_flag == REDIR_INPUT)
		cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, cmd->in_flag);
	if (cmd->outfile && cmd->out_flag == REDIR_OVERWRITE)
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
	if (cmd->outfile && cmd->out_flag == REDIR_APPEND)
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
}
