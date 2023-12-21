#include "minishell.h"

//it sends output redirects in the command table

int	redirects_cmd_tab(t_data *pntr, t_tab_cmd *tab_cmd, int i)
{
	
	return (0);
}

//it manages input & output redirects for the command table

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

//it waits for childs for end & updates the exit code which
//based on the status of child process

void	wait_for_childs(t_data *pntr)
{
	int	i;
	int	status;

	i = 0;
	while(pntr->cmdt_count > i)
		if (pntr->cmdt[i].is_child_process == 1)
			waitpid(pntr->cmdt[i].pid, &status, 0);
	if (pntr->cmdt[i - 1].is_child_process == 1)
	{
		if (WIFEXITED(status))
			pntr->code_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			pntr->code_exit = WTERMSIG(status) + 128;
	}
}

//sets the output & input file descriptors for a command table based on the specified input & output files or the next & previous files descriptors
int	change_fd_input_output(t_data *pntr, t_tab_cmd *tab_cmd, int *fd, int i)
{
	if (tab_cmd->file_in != -1)
		tab_cmd->in_fd = tab_cmd->file_in;
	else if (pntr->fd_before != -1 && i != 0)
		tab_cmd->in_fd = pntr->fd_before;
	if (tab_cmd->out_file != -1)
		tab_cmd->out_fd = tab_cmd->out_file;
	else if (fd[1] != -1 && pntr->cmdt_count - 1 != i)
		tab_cmd->out_fd = fd[1];
	return (0);
}

void	exec_main(t_data *data)
{
	t_cmd	*tmp;
	int		i;
	int		pip[2];

	i = 0;
	if (!data->cmd)
		return ;
	tmp = data->cmd;
	while(tmp)
	{
		if (i == 0 && data->cmdt->in_fd < 0)
			tmp->fd[0] = data->cmdt->in_fd;
		tmp->cmd_path = cmd_fullpath(data, tmp->args[0]);
		if (tmp->next)
			ft_pipe(tmp);
		else if (data->cmdt->out_fd < 0)
			tmp->fd[1] = data->cmdt->out_fd;
		if (!tmp->cmd_path)
			my_error("Command unknown\n");
		else
			run_cmd(tmp->args, tmp->cmd_path, tmp->fd[0], tmp->fd[1]);
		tmp = tmp->next;
	}


}

void	alt_exec_main(t_data *data)
{
	int	i;
	int	pip[2];

	i = 0;
	//put field in data struct holding state of previous fd to -1
	data->fd_before = -1;
	while(i < data->cmdt_count)
	{
		if (pipe(pip) == -1)
			return ((void)error_out(data, 1));
		//manage the redirection of input and output for a command in a pipeline
		if (pipelines_redirect(data, i, pip) && input_output_redirect(data, &data->cmdt[i]) == 1)
			;
		//then
		//sets the input and output file descriptors for a command table based on the specified input & output files or the previous files descriptors
		change_fd_input_output(data, &data->cmdt[i], pip, i);
		//then
		//if (check the command for builtins)
			//execute the builtin command
		//else
		i++;
	}
	wait_for_childs(data);
}
