#include "minishell.h"


int	redirect_check(t_cmd *cmd)
{
	if (cmd->doc)
		if(heredoc_create(cmd) == ERROR)
			return (ERROR);
	if (cmd->infile && cmd->in_flag == REDIR_INPUT)
	{
		cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, cmd->in_flag);
		if (!cmd->fd_in || cmd->fd_in == ERROR)
			return (ERROR);
	}
	else if (cmd->outfile && cmd->out_flag == REDIR_OVERWRITE)
	{
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
		if (!cmd->fd_out || cmd->fd_out == ERROR)
			return (ERROR);
	}
	else if (cmd->outfile && cmd->out_flag == REDIR_APPEND)
	{
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
		if (!cmd->fd_out || cmd->fd_out == ERROR)
			return (ERROR);
	}
    else if (cmd->in_flag == REDIR_HEREDOC)
		cmd->fd_in = heredoc_use(cmd);
	return (NO_ERROR);
}



