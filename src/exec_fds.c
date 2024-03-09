/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:26 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/09 14:47:14 by ycyr-roy         ###   ########.fr       */
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
	if (fd == -1)
		return (shell_error());
	return (fd);
}

void clean_heredocs_files(t_cmd *cmd)
{
	t_doc	*doc;
	t_doc	*tmp;

	doc = cmd->doc;
	while (doc)
	{
		tmp = doc;
		doc = doc->next;
		unlink(tmp->name);
		gc_free_one(get_data()->memblock, tmp->name);
		gc_free_one(get_data()->memblock, tmp->eof);
		gc_free_one(get_data()->memblock, tmp);
	}
}