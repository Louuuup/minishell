#include "minishell.h"

int	ft_pipe(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (DEBUG_ON)
		printf("(ft_pipe) ft_pipe called\n");
	if (pipe(pipe_fd) == -1)
		return (error_str("pipe error\n"));
	cmd->fd_out = pipe_fd[1];
	cmd->next->fd_in = pipe_fd[0];

	return (NO_ERROR);
}

int	ft_dup2(t_cmd *cmd)
{
	if (DEBUG_ON)
		printf("(ft_dup2) ft_dup2 called\n");
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

int	fd_redirect(int fd, char *file, int redir_flag)
{
	if (fd > 0)
		close(fd);
	if (redir_flag == REDIR_INPUT)
		fd = open(file, O_RDONLY);
	else if (redir_flag == REDIR_OVERWRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_flag == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//	else if (redir_flag == REDIR_HEREDOC)
	else
		return (error_str("redir_flag error\n"));
	if (fd == -1)
		return (shell_error());
	return (fd);
}
