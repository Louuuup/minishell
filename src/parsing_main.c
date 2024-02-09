#include "minishell.h"

// Reads and parses user_prompt. Returns 0 if no error, else returns error code.
int parser(t_data *data)
{
	//(void)data->user_prompt;
	int i;

	i = 0;
	// checks for unclosed quote
	if(!(ft_closedquote(data->user_prompt)))
	{
		ft_printf_fd(2, "unclosed quote\n");
		//free readline ??
		//make an error list ??
	}
	if(!ft_pipeparse(data->user_prompt))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `|'\n");
	}
	ft_cmdcount(data->user_prompt);
	
	char *temp;
	//change this allocation for the garbage collector one
	data->parser.cmd_list = gc_malloc((ft_cmdcount(data->user_prompt) + 1) * sizeof(char *));
	temp = ft_strtok(data->user_prompt, '|');
    while (temp) 
	{
		data->parser.cmd_list[i] = temp;
		i++;
        temp = ft_strtok(0, '|');
    }
	data->parser.cmd_list[i] = NULL;
	tokenizer(data);
	return (NO_ERROR);
}

// (move if needed) Reads and tokenizes user_prompt. Returns 0 if no error, else returns error code.
int	tokener(t_data *data)
{
	(void)data;
	return (NO_ERROR);
}
