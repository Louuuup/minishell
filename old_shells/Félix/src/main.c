
#include "../include/minishell.h"

/*void ft_close(t_info *inf)
{
	inf->cmd_list = inf->head;

	while(inf->cmd_list)
	{
		close(inf->cmd_list->fd_in);
		close(inf->cmd_list->fd_out);
		inf->cmd_list = inf->cmd_list->next;
	}
	inf->cmd_list = inf->head;
}*/

void	ft_close(t_cmd *cmd)
{
	//close(cmd->fd_in);
	close(cmd->fd_out);
}

int index_command(t_info *inf)
{
	t_cmd *temp;

	inf->cmd_count = 0;
	temp = inf->cmd_list;
	if (temp)
		inf->cmd_count++;
	while(temp)
	{
		temp->index = inf->cmd_count;
		inf->cmd_count++;
		temp = temp->next;
	}
	if (inf->cmd_count >= 1)
		return (SUCESS);
	else
		return (FAILURE);
}

int	ft_redirection(t_info *inf)
{
	ft_inputredir(inf->cmd_list);
	ft_outputredir(inf->cmd_list);
	return (0);
}

int	ft_pipe(t_info *inf)
{
	int fd[2];

	if (pipe(fd)){
		return (FAILURE);}
	{
		inf->cmd_list->fd_out = fd[1];
		inf->cmd_list->next->fd_in = fd[0];
	}
	return (SUCESS);
}

void ft_cmdloop(t_info *inf)
{
	index_command(inf);
	while (inf->cmd_list != NULL)
	{
		if (inf->cmd_list)
		{
			if(inf->cmd_list->index == 1)
			{
				inf->cmd_list->in_type = REDIR_HEREDOC;
				inf->cmd_list->out_type = REDIR_PIPE;
			}
			/*if(inf->cmd_list->index == 2)
			{
				inf->cmd_list->in_type = REDIR_PIPE;
				inf->cmd_list->out_type = REDIR_PIPE;
			}*/
			if(inf->cmd_list->index == 2)
			{
				inf->cmd_list->in_type = REDIR_PIPE;
				inf->cmd_list->out_type = REDIR_APPEND;
			}
			if(inf->cmd_list->next)
				ft_pipe(inf);
			ft_redirection(inf);
			ft_execute(inf);
			ft_close(inf->cmd_list);
		}
		inf->cmd_list = inf->cmd_list->next;
	}
	inf->cmd_list = inf->head;	
}

int	ft_temptakecommand(int argc, char **argv, t_info *info)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		ft_cmdadd_back(&info->cmd_list, ft_lstnewcmd(argv[i]));
		i++;
	}
	info->head = info->cmd_list;
	if (info->head != NULL)
		return (SUCESS);
	else
		return (FAILURE);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_cmd	cmd;
	int		i;
	char	*str;

	i = argc;
	if (argv)
		i++;
	ft_initstruct(&info, envp);
 	while (true)
 	{
    	str = readline("Minishell :");
		info.cmd_list = &cmd;
		info.cmd_list->cmd = ft_split(str, ' ');
		//printf("%s\n", info.cmd_list->command);
		ft_builtincheck(&cmd);
    	ft_execute(&info);
		waitpid(info.cmd_list->pid, NULL, 0);
    	free(str);
	}
}*/

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		i;

	i = argc;
	if (argv)
		i++;
	ft_initstruct(&info, envp);
	ft_temptakecommand(argc, argv, &info);
	ft_cmdloop(&info);
	info.cmd_list = info.head;
	//ft_close(&info);
	while (info.cmd_list != NULL)
	{
		waitpid(info.cmd_list->pid, NULL, 0);
		info.cmd_list = info.cmd_list->next;
	}
}

/*int ft_inputredir(t_cmd *cmd)
{
	int fd[2];

	if (cmd->next)
	{
		pipe(fd);
		cmd->fd_out = fd[1];
		cmd->next->fd_in = fd[0];
	}
	else
		ft_outputredir(cmd);
	return(SUCESS);
}*/

/*
input 	- NONE
		- PIPE
		- FILE
		- HEREDOC

output 	-NONE
		-PIPE
		-Outfile
		-APPEND
*/

int	ft_inputredir(t_cmd *cmd)
{
	if (cmd->in_type == REDIR_NONE)
		return(ft_stdin(cmd));
	else if (cmd->in_type == REDIR_INPUT)
		return(ft_infile(cmd));
	else if (cmd->in_type == REDIR_HEREDOC)
		return(ft_heredoc(cmd));
	else if (cmd->in_type == REDIR_PIPE)
		return (SUCESS);
	return (FAILURE);
}
int	ft_outputredir(t_cmd *cmd)
{
	if (cmd->out_type == REDIR_NONE)
		return(ft_stdout(cmd));
	else if (cmd->out_type == REDIR_OVERWRITE)
		return(ft_outfile(cmd));
	else if (cmd->out_type == REDIR_APPEND)
		return(ft_append(cmd));
	else if(cmd->out_type == REDIR_PIPE)
		return (SUCESS);
	return (FAILURE);
}
