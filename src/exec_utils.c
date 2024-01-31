#include "minishell.h"

int	ft_pipe(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (error_str("pipe error\n"));
	cmd->fd_out = pipe_fd[1];
	cmd->next->fd_in = pipe_fd[0];

	return (NO_ERROR);
}

int	ft_dup2(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			return (error_str("dup2 error\n"));
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			return (error_str("dup2 error\n"));
		close(cmd->fd_out);
	}
	return (NO_ERROR);
}
