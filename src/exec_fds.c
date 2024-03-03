#include "minishell.h"


/*int	fd_redirect(int fd, char *file, int redir_flag) 
{
	if (fd > 2)
		close(fd);
	if (redir_flag == REDIR_INPUT)
		fd = open(file, O_RDONLY);
	else if (redir_flag == REDIR_OVERWRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_flag == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (error_str("redir_flag error\n"));
	if (fd == -1)
		return (shell_error());
	if ((access(file, W_OK)) == -1)
	{	
		error_str_file("permission denied: ", file);
		return (0);
	}
	return (fd);
}*/


int	redirect_check(t_cmd *cmd)
{
	if (cmd->doc)
		heredoc_create(cmd);
	if (cmd->infile && cmd->in_flag == REDIR_INPUT)
	{
		cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, cmd->in_flag);
		if (!cmd->fd_in)
			return (ERROR);
	}
	else if (cmd->outfile && cmd->out_flag == REDIR_OVERWRITE)
	{
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
		if (!cmd->fd_out)
			return (ERROR);
	}
	else if (cmd->outfile && cmd->out_flag == REDIR_APPEND)
	{
		cmd->fd_out = fd_redirect(cmd->fd_out, cmd->outfile, cmd->out_flag);
		if (!cmd->fd_out)
			return (ERROR);
	}
    else if (cmd->in_flag == REDIR_HEREDOC)
		cmd->fd_in = heredoc_use(cmd);
	return (NO_ERROR);
}



