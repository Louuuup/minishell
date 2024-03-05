#include "minishell.h"

void close_fds(t_cmd *cmd)
{
	t_cmd *tmp;

	if (DEBUG_ON)
		printf("(close_fds) close_fds called\n");
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = tmp;
	}
}


void	clean_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_data *data;

	data = get_data();
	if (DEBUG_ON)
		printf("(clean_cmd) clean_cmd called\n");
	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->cmd)
			gc_free_one(data->memblock, cmd->cmd);
		if (cmd->infile)
			gc_free_one(data->memblock, cmd->infile);
		if (cmd->outfile)
			gc_free_one(data->memblock, cmd->outfile);
		if (cmd->doc)
			ft_cleardoclst(&cmd->doc);
		gc_free_one(data->memblock, cmd);
		cmd = tmp;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	data = get_data();
	(void)argv; //not needed
	(void)argc; //not needed
	init_all(data, envp); //initialises all data
	signal(SIGQUIT, SIG_IGN);
	while (TRUE) //main loop
	{
		signal(SIGINT, sig_inthandler);
		data->user_prompt = readline(PROMPT_NAME);
		if (data->user_prompt && !ft_strncmp(data->user_prompt, "\0", 2)) //if user input is empty
		{
			get_data()->code_exit = 0;
			free(data->user_prompt);
			data->user_prompt = NULL;
		}
		else if(data->user_prompt == NULL) //dans le cas d'un ctrl-D
		{
			gc_free_all(data->memblock);
			break; //free everyting and exit the shell
		}
		else //if user input is not empty
		{
			if (DEBUG_ON)
				printf("(main) prompt detected\n");
			add_history(data->user_prompt);
			if (parser(data))
			{
				exec_main(data);
				wait_pid(data);
				ft_freeparse(data);
				close_fds(data->cmd);
				clean_cmd(data->cmd);
			}	
		}
		dprintf(2 ,"exit code : %d\n", data->code_exit);
	}
	return (NO_ERROR); //renvoyé le dernier code d'erreur
}
