#include "minishell.h"

int	heredoccheck(void)
{
	pid_t 	pid;

	pid = fork();
	if (pid < 0)
		error_str("fork error\n");
	if (pid == 0)
		child_routine(pid);
	else if (pid > 0)
		return(parent_routine(pid));
	if(pid == 0)
		kill(0, SIGTERM);
	printf("not suppose to be here\n");
	return (ERROR);
}

int is_directory(char *cmd) 
{
    struct stat statbuf;
	
    if (stat(cmd, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

int	setcmdlist(t_data *data)
{
	char	*temp;
	int		i;

	i = ft_cmdcount(data->user_prompt);
	data->parser.cmd_list = NULL;
	data->parser.free = NULL;
	data->parser.cmd_list = gc_malloc((i + 2) * sizeof(char *));
	data->parser.free = gc_malloc((i + 2) * sizeof(char **));
	temp = ft_strtok(data->user_prompt, '|');
	i = 0;
	while (temp)
	{
		data->parser.cmd_list[i] = temp;
		i++;
		temp = ft_strtok(0, '|');
	}
	data->parser.cmd_list[i] = NULL;
	return (1);
}

// Reads and parses user_prompt. Returns 0 if error, else returns error code.
int	parser(t_data *data)
{
	if (DEBUG_ON)
		printf("(parser) parser called\n");
	if (!data->user_prompt)
		return (0);
	if (!(ft_closedquote(data->user_prompt)))
		return (unclosedqtes(data));
	if (!ft_pipeparse(data->user_prompt))
		return (pipeerr(data));
	setcmdlist(data);
	if (!tokenizer(data))
		return (0); //add different error maybe
	return (1);
}
