#include "minishell.h"

//it manages input & output redirects for the command table

int	input_output_redirect(t_data *pntr, t_tab_cmd *tab_cmd)
{
	int	i;

	i = 0;
	while (tab_cmd->num_redirections > i)
	{
		if (tab_cmd->redirections[i].no_space == 2 && tab_cmd->redirections[i].type != REDIRECT_MULTILINE)
		{
			ft_putnbr_fd(2, "minishell: redirect to nowhere\n");
			pntr->
		}
		i++;
	}
	return (0);
}

// void	run_cmd(char **args, char *cmd_path, int in_fd, int out_fd)
// {

// }

void	exec_main(t_data *data)
{
	t_cmd	*tmp;

	if (!data->cmd)
		return ;

	tmp = data->cmd;
	while(tmp)
	{
		if (tmp->)
		tmp = tmp->next;
	}


}
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
		//then
		//if (check the command for builtins)
			//execute the builtin command
		//else
		i++;
	}
