#include "minishell.h"

void	recreate_file_descriptors(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd)
{
	
	write(1, "1", 1);
}

//it creates file descriptors for input/output in the builtin command
//finishes a pipe file descriptor

void    create_builtin_fd(t_tab_cmd *cmd_tab, int *pipe_fd)
{
	if (cmd_tab->out_fd != -1)
		dup2(cmd_tab->out_fd, STDOUT_FILENO);
	if (cmd_tab->in_fd != -1)
	{
		dup2(cmd_tab->in_fd, STDIN_FILENO);
		if (cmd_tab->in_fd != -1)
			close(cmd_tab->in_fd);
	}
	close(pipe_fd[1]);
}

void    shoot_builtin(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd)
{
	create_builtin_fd(cmd_tab, pipe_fd);
	if (ft_strcmp(cmd_tab->cmd, "exit") == 0)
		// built_exit(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "env") == 0)
		// built_env(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "unset") == 0)
		// built_unset(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "export") == 0)
		// built_export(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "pwd") == 0)
		// built_pwd(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "cd") == 0)
		// built_cd(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "echo") == 0)
		// built_echo(pntr, cmd_tab);
	recreate_file_descriptors(pntr, cmd_tab, i, pipe_fd);
}

int	if_builtin(t_tab_cmd *cmd_tab)
{
	if (ft_strcmp(cmd_tab->cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_tab->cmd, "echo") == 0)
		return (1);
	return (0);
}
