#include "minishell.h"

int setcmdlist(t_data *data)
{
	char *temp;
	int i;

	i = 0;	

	data->parser.cmd_list = NULL;
	data->parser.sgl_cmd = NULL;
	data->parser.cmd_list = gc_malloc((ft_cmdcount(data->user_prompt) + 1) * sizeof(char *));
	data->parser.free = gc_malloc((ft_cmdcount(data->user_prompt) + 1) * sizeof(char **));
	temp = ft_strtok(data->user_prompt, '|');
    while (temp) 
	{
		data->parser.cmd_list[i] = temp;
		i++;
        temp = ft_strtok(0, '|');
    }
	data->parser.cmd_list[i] = NULL;
	return(1);
}

// Reads and parses user_prompt. Returns 0 if error, else returns error code.
int parser(t_data *data)
{
	if (DEBUG_ON)
		printf("(parser) parser called\n");
	if(!data->user_prompt)
		return(0);	
	if(!(ft_closedquote(data->user_prompt)))
		return(unclosedqtes(data));
	if(!ft_pipeparse(data->user_prompt))
		return(pipeerr(data));
	setcmdlist(data);
	if(!tokenizer(data))
		return(0); //add different error maybe
	return (1);
}
