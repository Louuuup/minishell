#include "minishell.h"

int heredoc_create(t_cmd *cmd, t_doc *doc)
{
	char *line;
	t_doc *tmp;

	tmp = doc;
	while(tmp)
	{
		// create file
		while (1)
		{
			line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, doc->eof) == 0)
			{
				free(line);
				break;
			}
			// addline to file
			write(STDIN_FILENO, line, ft_strlen(line));
			write(STDIN_FILENO, "\n", 1);
			free(line);
		}
		tmp = tmp->next;
	}
	return (NO_ERROR);
}

int	fd_redirect(int fd, char *file, int redir_flag) 
{
	if (fd > 2)
		close(fd);
	if (redir_flag == REDIR_INPUT)
		fd = open(file, O_RDONLY);
	else if (redir_flag == REDIR_OVERWRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_flag == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir_flag == REDIR_HEREDOC)
		;
	else
		return (error_str("redir_flag error\n"));
	/*if (fd == -1)
		return (shell_error());*/
	if ((access(file, W_OK)) == -1)
	{	
		error_str_file("permission denied: ", file);
		return (0);
	}
	return (fd);
}


int	redirect_check(t_cmd *cmd)
{
	if (cmd->doc)
	{
		heredoc_create(cmd, cmd->doc);
	}
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
    else if (cmd->infile && cmd->in_flag == REDIR_HEREDOC)
    {
        cmd->fd_in = fd_redirect(cmd->fd_in, cmd->infile, cmd->in_flag);
		if (!cmd->fd_in)
			return (ERROR);
    }
	return (NO_ERROR);
}



