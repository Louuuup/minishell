#include "../../include/minishell.h"

int check_arguments(t_type_token type)
{
	if (type == SQUOTE || type == DQUOTE || type == WORD)
		return (1);
	return (0);
}

int check_if_redirection(t_type_token type)
{
	if (type == WORD || type == SQUOTE || type == DQUOTE || type == PIPE)
		return (1);
	return (0);
}

