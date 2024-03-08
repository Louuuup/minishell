/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:26 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 15:00:22 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_check(t_cmd *cmd)
{
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

int fd_redirect_others(int fd, char *file, int redir_flag)
{
	fd = 0;
	if (redir_flag == REDIR_OVERWRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((access(file, W_OK)) == -1)
		{
			get_data()->code_exit = 1;
			return (error_str_file("permission denied: ", file));
		}
	}
	else if (redir_flag == REDIR_APPEND)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((access(file, W_OK)) == -1)
		{	
			get_data()->code_exit = 1;
			return (error_str_file("permission denied: ", file));
		}
	}
	return (fd);
}


int	fd_redirect(int fd, char *file, int redir_flag) 
{
	if (fd > 2)
		close(fd);
	if (redir_flag == REDIR_INPUT)
	{
		fd = open(file, O_RDONLY);
		if (access(file, R_OK) == -1)
		{
			get_data()->code_exit = 1;
			return (error_str_file("permission denied: ", file));
		}
	}
	else if (redir_flag == REDIR_OVERWRITE || redir_flag == REDIR_APPEND)
		fd = fd_redirect_others(fd, file, redir_flag);
	else
		return (error_str_code("redir_flag error\n", NULL, 1));
		// return (error_str("redir_flag error\n"));
	if (fd == -1)
		return (shell_error());
	return (fd);
}
