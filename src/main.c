/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:43 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/09 01:04:28 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void cleanup(t_data *data, t_cmd *cmd)
{
	ft_freeparse(data);
	close_fds(cmd);
}

static void main_process(t_data *data)
{
	if (heredoccheck() != ERROR)
	{
		if (data->code_exit == 127)
			data->code_exit = 0;
		exec_main(data);
		wait_pid(data);
		cleanup(data, data->cmd);
	}
	else
		cleanup(data, data->cmd);
}

int main(int argc, char *argv[], char *envp[])
{
	t_data *data;

	data = init_all(envp, argv, argc);
	while (TRUE)
	{
		signal(SIGINT, sig_inthandler);
		data->user_prompt = readline(PROMPT_NAME);
		if (data->user_prompt && !ft_strncmp(data->user_prompt, "\0", 2))
		{
			exit_code(0);
			data->user_prompt = free_null(data->user_prompt);
		}
		else if(data->user_prompt == NULL)
			b_exit(NULL);
		else
		{
			add_history(data->user_prompt);
			if (parser(data))
				main_process(data);
		}
		//dprintf(2 ," exit code : %d\n", data->code_exit);
	}
	return (data->code_exit); //renvoyé le dernier code d'erreur
}
