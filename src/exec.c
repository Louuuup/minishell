#include "minishell.h"


void	fd_cleaning(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	if (tab_cmd->out_fd	!= -1)
		close(tab_cmd->out_fd);
	else if (tab_cmd->in_fd != -1)
		close(tab_cmd->in_fd);
	if (pntr->cmdt[i].last_multiline)
	{
		unlink(pntr->cmdt[i].last_multiline);
		free(pntr->cmdt[i].last_multiline);
	}
}

void	total_clean(t_data *pntr)
{

}

// The function creates a child process to execute the specified command, handling input and output redirection, executes the commands using execve and managing file descriptors in the parent process.

void	command_execution(t_data *pntr, t_tab_cmd *tab_cmd, int i, int *fd_pipe)
{
	tab_cmd->pid = fork();

	if (tab_cmd->pid < 0)
		return ((void)error_out(pntr, 1));
	if (!tab_cmd->pid)
	{
		if (dup2(tab_cmd->in_fd, STDIN_FILENO) && tab_cmd->in_fd != -1)
			close(tab_cmd->in_fd);
		close(fd_pipe[0]);
		if (dup2(tab_cmd->out_fd, STDOUT_FILENO) && tab_cmd->out_fd != -1)
			close(tab_cmd->out_fd);
		set_mode(pntr, CHILD);
		execve(tab_cmd->cmd, tab_cmd->args, pntr->env);
		error_out(pntr, 1);
		total_clean(pntr);
		exit(1);
	}
	close(fd_pipe[1]);
	if (pntr->fd_before != -1)
		close(pntr->fd_before);
	if (pntr->cmdt_count - 1 != i)
		pntr->fd_before = fd_pipe[0];
	else
		close(fd_pipe[0]);
	fd_cleaning(pntr, tab_cmd, i);
}

//function, redirects_cmd_tab, handles the redirections for a command in the t_tab_cmd structure based on the type of redirection specified. function, redirects_cmd_tab, handles the redirections for a command in the t_tab_cmd structure based on the type of redirection specified.

int	redirects_cmd_tab(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	if (tab_cmd->redirections[i].type == REDIRECT_MULTILINE)
	{
		if (create_heredoc(pntr, tab_cmd, i) == 1)
			return (1);		
	}
	else if (tab_cmd->redirections[i].type == REDIRECT_APPEND)
	{
		if (tab_cmd->file_out == -1)
			return (error_out(pntr, 1));
		if (tab_cmd->file_out != -1)
			close(tab_cmd->file_out);
		tab_cmd->file_out = open(tab_cmd->redirections[i].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (tab_cmd->redirections[i].type == REDIRECT_OUT)
	{
		if (tab_cmd->file_out == -1)
			return (error_out(pntr, 1));
		if (tab_cmd->file_out != -1)
			close(tab_cmd->file_out);
		tab_cmd->file_out = open(tab_cmd->redirections[i].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return (0);
}

//This function, input_output_redirect, manages input and output redirection for a command specified in the t_tab_cmd structure

int	input_output_redirect(t_data *pntr, t_tab_cmd *tab_cmd)
{
	int	i;

	i = 0;
	while (tab_cmd->num_redirections > i)
	{
		if (tab_cmd->redirections[i].type != REDIRECT_MULTILINE && tab_cmd->redirections[i].no_space == 2)
		{
			ft_putstr_fd("minishell: re-direction to nowhere\n", 2);
			pntr->code_exit = 1;
			return (1);
		}
		if (tab_cmd->redirections[i].type == REDIRECT_IN)
		{
			if (tab_cmd->file_in != -1)
				close(tab_cmd->file_in);
			tab_cmd->file_in = open(tab_cmd->redirections[i].value, O_RDONLY);
			if (tab_cmd->file_in == -1)
				return (error_out(pntr, 1));
		}
		else if (redirects_cmd_tab(pntr, tab_cmd, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

//This function, wait_for_childs, is responsible for waiting for the child processes to complete and updating the exit status of the minishell accordingly

void	wait_for_childs(t_data *pntr)
{
	int	i;
	int	status;

	i = 0;
	while(pntr->cmdt_count > i)
	{
		if (pntr->cmdt[i].is_child_process == 1)
			waitpid(pntr->cmdt[i].pid, &status, 0);
	}
	if (pntr->cmdt[i - 1].is_child_process == 1)
	{
		if (WIFSIGNALED(status))
			pntr->code_exit = WTERMSIG(status) + 128;
		else if (WIFEXITED(status))
			pntr->code_exit = WEXITSTATUS(status);
	}
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;
}

void	exec_main(t_data *data)
{
	t_cmd	*tmp;
	int		pip[2];

	if (!data->cmd)
		return ;
	tmp = data->cmd;
	while(tmp)
	{
		if (tmp->cmd_idx == 0 && data->cmdt->in_fd > 0)
			tmp->fd[0] = data->cmdt->in_fd;
		else if (tmp->cmd_idx < 0)
			tmp->fd[0] = pip[1];
		tmp->cmd_path = cmd_fullpath(data, tmp->args[0]);
		if (tmp->next)
			ft_pipe(tmp);
		else if (data->cmdt->out_fd < 0)
			tmp->fd[1] = data->cmdt->out_fd;
		if (!tmp->cmd_path)
			my_error("Command unknown\n");
		if (tmp->next) //if there is another cmd after pipe
			exec_cmd(data, tmp);
		if (pipe(pip) == -1)
			ft_error(ERR_PIPE);
		tmp = tmp->next;
	}
}

void	alt_exec_main(t_data *pntr)
{
	int	i;
	int	pip[2];

	i = -1;
	pntr->fd_before = -1;
	while(pntr->cmdt_count > ++i)
	{
		if (pipe(pip) == -1)
			return ((void)error_out(pntr, 1));
		if (pipelines_redirect(pntr, i, pip) && input_output_redirect(pntr, &pntr->cmdt[i]) == 1)
			continue ;
		change_fd_input_output(pntr, &pntr->cmdt[i], pip, i);
		if (if_builtin(&pntr->cmdt[i]) == 1)
			shoot_builtin(pntr, &pntr->cmdt[i], i, pip);
		else
		{
			if (++pntr->cmdt[i].is_child_process && find_exec(pntr, &pntr->cmdt[i]) == 0)
				command_execution(pntr, &pntr->cmdt[i], i, pip);
			else
				pipelines_redirect(pntr, i, pip);
		}
		i++;
	}
	wait_for_childs(pntr);
}
