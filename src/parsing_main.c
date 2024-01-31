#include "minishell.h"

// Reads and parses user_prompt. Returns 0 if no error, else returns error code.
int parser(t_data *data)
{
	//(void)data->user_prompt;
	
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
	//handle and remove redirection
	//flag in the cmd list
	//
	char *temp;
	
	temp = ft_strtok(data->user_prompt, '|');
    while (temp) {
        printf("%s\n", temp);
        temp = ft_strtok(0, '|');
    }
	return (NO_ERROR);
}

// (move if needed) Reads and tokenizes user_prompt. Returns 0 if no error, else returns error code.
int	tokener(t_data *data)
{
	(void)data;
	return (NO_ERROR);
}
