#include "minishell.h"

// The function creates a child process to execute the specified command,
//handling input and output redirection, executes the commands using
//execve and managing file descriptors in the parent process.

void	command_execution(t_data *pnt, t_tab_cmd *tab_cmd, int i, int *fd_pipe)
{
	tab_cmd->pid = fork();
	if (tab_cmd->pid < 0)
		return ((void)error_out(pnt, "fork", 1));
	if (!tab_cmd->pid)
	{
		if (dup2(tab_cmd->in_fd, STDIN_FILENO) && tab_cmd->in_fd != -1)
			close(tab_cmd->in_fd);
		close(fd_pipe[0]);
		if (dup2(tab_cmd->out_fd, STDOUT_FILENO) && tab_cmd->out_fd != -1)
			close(tab_cmd->out_fd);
		set_mode(pnt, CHILD);
		execve(tab_cmd->cmd, tab_cmd->args, pnt->env);
		error_out(pnt, tab_cmd->cmd, 1);
		total_clean(pnt);
		exit(1);
	}
	close(fd_pipe[1]);
	if (pnt->fd_before != -1)
		close(pnt->fd_before);
	if (pnt->cmdt_count - 1 != i)
		pnt->fd_before = fd_pipe[0];
	else
		close(fd_pipe[0]);
	fd_cleaning(pnt, tab_cmd, i);
}

//function, redirects_cmd_tab, handles the redirections for a command in
//the t_tab_cmd structure based on the type of redirection specified.
//function, redirects_cmd_tab, handles the redirections for a command in
//the t_tab_cmd structure based on the type of redirection specified.

int	redirects_cmd_tab(t_data *pnt, t_tab_cmd *tab_cmd, int i)
{

	if (tab_cmd->redirections[i].type == REDIRECT_OUT)
	{
		if (tab_cmd->file_out != -1)
			close(tab_cmd->file_out);
		tab_cmd->file_out = open(tab_cmd->redirections[i].value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tab_cmd->file_out == -1)
			return (error_out(pnt, tab_cmd->redirections[i].value,1));
	}
	else if (tab_cmd->redirections[i].type == REDIRECT_APPEND)
	{
		if (tab_cmd->file_out != -1)
			close(tab_cmd->file_out);
		tab_cmd->file_out = open(tab_cmd->redirections[i].value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tab_cmd->file_out == -1)
			return (error_out(pnt, tab_cmd->redirections[i].value, 1));
	}
	else if (tab_cmd->redirections[i].type == REDIRECT_MULTILINE)
		if (create_heredoc(pnt, tab_cmd, i) == 1)
			return (1);
	return (0);
}

//This function, input_output_redirect, manages input and output
//redirection for a command specified in the t_tab_cmd structure

int	input_output_redirect(t_data *pnt, t_tab_cmd *tab_cmd)
{
	int	i;

	i = -1;
	while (tab_cmd->num_redirections > ++i)
	{
		if (tab_cmd->redirections[i].type != REDIRECT_MULTILINE
			&& tab_cmd->redirections[i].no_space == 2)
		{
			ft_printf_fd(2, "minishell: redirect to nowhere\n");
			pnt->code_exit = 1;
			return (1);
		}
		if (tab_cmd->redirections[i].type == REDIRECT_IN)
		{
			if (tab_cmd->file_in != -1)
				close(tab_cmd->file_in);
			tab_cmd->file_in = open(tab_cmd->redirections[i].value, O_RDONLY);
			if (tab_cmd->file_in == -1)
				return (error_out(pnt, tab_cmd->redirections[i].value, 1));
		}
		else if (redirects_cmd_tab(pnt, tab_cmd, i) == 1)
			return (1);
	}
	return (0);
}

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

//This function, wait_for_childs, is responsible for waiting for the
//child processes to complete and updating the exit status of the
//minishell accordingly

void	wait_for_childs(t_data *pnt)
{
	int	i;
	int	status;

	i = -1;
	while (pnt->cmdt_count > ++i)
	{
		if (pnt->cmdt[i].is_child_process == 1)
			waitpid(pnt->cmdt[i].pid, &status, 0);
	}
	if (pnt->cmdt[i - 1].is_child_process == 1)
	{
		if (WIFSIGNALED(status))
			pnt->code_exit = WTERMSIG(status) + 128;
		else if (WIFEXITED(status))
			pnt->code_exit = WEXITSTATUS(status);
	}
}

// void	exec_cmd(t_data *data, t_cmd *cmd)
// {
// 	(void)data;
// 	(void)cmd;
// }

// void	exec_main(t_data *data)
// {
// 	t_cmd	*tmp;
// 	int		pip[2];

// 	if (!data->cmd)
// 		return ;
// 	tmp = data->cmd;
// 	while (tmp)
// 	{
// 		if (tmp->cmd_idx == 0 && data->cmdt->in_fd > 0)
// 			tmp->fd[0] = data->cmdt->in_fd;
// 		else if (tmp->cmd_idx < 0)
// 			tmp->fd[0] = pip[1];
// 		tmp->cmd_path = cmd_fullpath(data, tmp->args[0]);
// 		if (tmp->next)
// 			ft_pipe(tmp);
// 		else if (data->cmdt->out_fd < 0)
// 			tmp->fd[1] = data->cmdt->out_fd;
// 		if (!tmp->cmd_path)
// 			my_error("Command unknown\n");
// 		if (tmp->next) //if there is another cmd after pipe
// 			exec_cmd(data, tmp);
// 		if (pipe(pip) == -1)
// 			ft_error(ERR_PIPE);
// 		tmp = tmp->next;
// 	}
// }

//the function is responsible for managing the execution of multiple
//commands in a shell program, handling pipelines, redirections, and
//executing both built-in and external commands.

void	alt_exec_main(t_data *pnt)
{
	int	i;
	int	pip[2];

	i = -1;
	pnt->fd_before = -1;
	while (pnt->cmdt_count > ++i)
	{
		// printf("(alt_exec_main) -> cmd = %s\n", pnt->cmdt[i].cmd); //debug
		// printf("(alt_exec_main) -> num_args = %d\n", pnt->cmdt[i].num_args); //debug
		// printf("(alt_exec_main) -> cmdt_count = %d\n", pnt->cmdt_count); //debug

		//finds if env exists
		// if (pnt->env)
		// 	printf("(alt_exec_main) -> env exists\n"); //deubg
		if (pipe(pip) == -1)
			return ((void)error_out(pnt, "pipe", 1));
		if (pipelines_redirect(pnt, i, pip)
			&& input_output_redirect(pnt, &pnt->cmdt[i]) == 1)
			continue ;
		change_fd_input_output(pnt, &pnt->cmdt[i], pip, i);
		if (if_builtin(&pnt->cmdt[i]) == 1)
			shoot_builtin(pnt, &pnt->cmdt[i], i, pip);
		else
		{
			if (++pnt->cmdt[i].is_child_process
				&& find_exec(pnt, &pnt->cmdt[i]) == 0)
				command_execution(pnt, &pnt->cmdt[i], i, pip);
			else
				pipelines_redirect(pnt, i, pip);
		}
	}
	wait_for_childs(pnt);
}
