#include "minishell.h"

//it's responsible for restoring file descriptors to their original states after executing a command

void	recreate_file_descriptors(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd)
{
	if (cmd_tab->out_fd != -1)
		close(cmd_tab->out_fd);
	if (pntr->cmdt_count - 1 != i)
		pntr->fd_before = pipe_fd[0];
	else
		close(pipe_fd[0]);
	dup2(pntr->first_stdout, STDOUT_FILENO);
	dup2(pntr->first_stdin, STDIN_FILENO);
	if (cmd_tab->in_fd != -1)
		close(cmd_tab->in_fd);
	if (cmd_tab->out_fd != -1)
		close(cmd_tab->out_fd);
	if (pntr->cmdt[i].last_multiline)
	{
		unlink(pntr->cmdt[i].last_multiline);
		free(pntr->cmdt[i].last_multiline);
	}
}

//it creates file descriptors for input/output in the builtin command
//finishes a pipe file descriptor

void	create_builtin_fd(t_tab_cmd *cmd_tab, int *pipe_fd)
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

//function checks which built-in command is requested in the current cmd_table and calls the
//corresponding function to handle the execution of that built-in command. After executing the
//built-in command, it calls restore_fds to restore file descriptors to their original state

void	shoot_builtin(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd)
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

//check whether a given command is a built-in command

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
