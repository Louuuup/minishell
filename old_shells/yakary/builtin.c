#include "minishell.h"

//recreate_file_descriptors is responsible for resetting file descriptors, closing unnecessary file descriptors, and performing cleanup tasks after executing a command in the shell.

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

//create_builtin_fd prepares the file descriptors for input and output redirection and handles pipes for a built-in command before its execution.

void	create_builtin_fd(t_tab_cmd *cmd_tab, int *pipe_fd)
{
	if (cmd_tab->in_fd != -1)
	{
		dup2(cmd_tab->in_fd, STDIN_FILENO);
		if (cmd_tab->in_fd != -1)
			close(cmd_tab->in_fd);
	}
	if (cmd_tab->out_fd != -1)
		dup2(cmd_tab->out_fd, STDOUT_FILENO);
	close(pipe_fd[1]);
}

//function checks which built-in command is requested in the current cmd_table and calls the
//corresponding function to handle the execution of that built-in command. After executing the
//built-in command, it calls restore_fds to restore file descriptors to their original state

void	shoot_builtin(t_data *pntr, t_tab_cmd *cmd_tab, int i, int *pipe_fd)
{
	// printf("(shoot_builtin) cmd_tab->cmd is %s.\n", cmd_tab->cmd); //debug
	create_builtin_fd(cmd_tab, pipe_fd);
	if (ft_strcmp(cmd_tab->cmd, "exit") == 0)
		built_exit(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "env") == 0)
		built_env(pntr);
	// if (ft_strcmp(cmd_tab->cmd, "unset") == 0)
		// built_unset(pntr, cmd_tab);
	if (ft_strcmp(cmd_tab->cmd, "export") == 0)
		built_export(pntr, cmd_tab, STDOUT_FILENO);
	if (ft_strcmp(cmd_tab->cmd, "pwd") == 0)
		build_pwd(pntr);
	if (ft_strcmp(cmd_tab->cmd, "cd") == 0)
		// built_cd(pntr, cmd_tab);
	// if (ft_strcmp(cmd_tab->cmd, "echo") == 0)
		// built_echo(pntr, cmd_tab);
	recreate_file_descriptors(pntr, cmd_tab, i, pipe_fd);
}

//This function, if_builtin, checks if a given command is a built-in command by comparing its name (cmd_tab->cmd) with a list of known built-in command names.

int	if_builtin(t_tab_cmd *tab_cmd)
{
	if (ft_strcmp(tab_cmd->cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(tab_cmd->cmd, "echo") == 0)
		return (1);
	return (0);
}
