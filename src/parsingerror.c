#include "minishell.h"

int	unclosedqtes(t_data *data)
{
	free(data->user_prompt);
	error_str("unclosed quote\n");
	return (0);
}

int	pipeerr(t_data *data)
{
	free(data->user_prompt);
	error_str("minishell: syntax error near unexpected token `|'\n");
	return (0);
}
