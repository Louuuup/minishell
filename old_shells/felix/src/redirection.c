
#include "../include/minishell.h"

int	ft_stdin(t_cmd *cmd)
{
	if(cmd)
	{
		cmd->fd_in = dup(STDIN_FILENO);
	}
	return(SUCESS);
}

int ft_infile(t_cmd *cmd)
{
	int	fd;

	fd = open (cmd->infile, O_RDONLY, 0777);
	if (fd < 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(cmd->infile, 2);
		//free
	}
	cmd->fd_in = fd;
	dup2(fd, STDIN_FILENO);
	return (SUCESS);
}

int ft_stdout(t_cmd *cmd)
{
	if(cmd)
	{
		cmd->fd_out = dup(STDOUT_FILENO);
	}
	return(SUCESS);
}

int ft_outfile(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(cmd->outfile, 2);
	}
	cmd->fd_out = fd;
	dup2 (fd, STDOUT_FILENO);
	return (SUCESS);
}

int ft_append(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(cmd->outfile, 2);
		//free
	}
	cmd->fd_out = fd;
	dup2 (fd, STDOUT_FILENO);
	return(SUCESS);
}