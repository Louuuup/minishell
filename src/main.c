#include "minishell.h"


void close_fds(t_cmd *cmd)
{
	t_cmd *tmp;

	if (DEBUG_ON)
		printf("(close_fds) close_fds called\n");
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->fd_in != 0 && cmd->fd_in != -1)
			close(cmd->fd_in);
		if (cmd->fd_out != 1 && cmd->fd_in != -1)
			close(cmd->fd_out);
		cmd = tmp;
	}
}


/*static void	clean_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_data *data;

	data = get_data();
	if (DEBUG_ON)
		printf("(clean_cmd) clean_cmd called\n");
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->cmd) 
			gc_free_one(data->memblock, (*cmd)->cmd);
		if ((*cmd)->infile)
			gc_free_one(data->memblock, (*cmd)->infile);
		if ((*cmd)->outfile)
			gc_free_one(data->memblock, (*cmd)->outfile);
		if ((*cmd)->doc)
			ft_cleardoclst(&(*cmd)->doc);
		gc_free_one(data->memblock, cmd);
		*cmd = tmp;
	}
	cmd = NULL;
}*/

void cleanup(t_data *data, t_cmd *cmd)
{
	ft_freeparse(data);
	close_fds(cmd);
	//clean_cmd(&cmd);
}

static void main_process(t_data *data)
{
	if (heredoccheck() != ERROR)
	{
		exec_main(data);
		wait_pid(data);
		cleanup(data, data->cmd);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	data = init_all(envp, argv, argc); //initialises all data
	while (TRUE) //main loop
	{
		signal(SIGINT, sig_inthandler);
		data->user_prompt = readline(PROMPT_NAME);
		if (data->user_prompt && !ft_strncmp(data->user_prompt, "\0", 2)) //if user input is empty
		{
			exit_code(0);
			data->user_prompt = free_null(data->user_prompt);
		}
		else if(data->user_prompt == NULL)
		{
			gc_free_all(data->memblock);
			break;
		}
		else //if user input is not empty
		{
			add_history(data->user_prompt);
			if (parser(data))
				main_process(data);
		}
		dprintf(2 ,"exit code : %d\n", data->code_exit);
	}
	return (NO_ERROR); //renvoyé le dernier code d'erreur
}
