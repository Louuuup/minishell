#include "minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	ft_error(char *str)
{
	ft_putstr_fd(ERR_MAIN, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	perror(ERR_EXP);
	// free_all(get_data());
	exit(ERROR);
}

void	my_error(char *str)
{
	ft_putstr_fd(ERR_MAIN, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	// free_all(get_data());
	exit (ERROR);
}

int error_out(t_data *pnt, char *s, int n)
{
	if (n == 1)
	{
		ft_printf_fd(2, "minishell: %s: ", s);
		perror("");
		pnt->code_exit = n;
	}
	return (1);
}
/*
frees the memory of a pointer and sets it to NULL
(protects against double free)
*/
void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// is designed to handle syntax errors in the input provided to the shell. It takes a type parameter to determine the specific type of syntax error and prints an appropriate error message along with setting the exit code for the shell.
// The types and their corresponding messages are as follows:

// 39: Unexpected single quote: prints "''\n"
// 0: Unexpected newline: prints "newline'\n"
// 34: Unexpected double quote: prints "\"'\n"
// 5: Unexpected token for here document (<<): prints "<<'\n"
// 4: Unexpected token for appending output (>>): prints ">>'\n"
// 3: Unexpected token for redirecting output (>): prints ">'\n"
// 2: Unexpected token for redirecting input (<): prints "<'\n"
// 1: Unexpected token for pipe (|): prints "|'\n"


void	error_in_syntax(int type, t_data *pntr)
{
	pntr->code_exit = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (type == 39)
		ft_putstr_fd("`''\n", 2);
	else if (type == 0)
		ft_putstr_fd("`newline'\n", 2);
	else if (type == 34)
		ft_putstr_fd("`\"'\n", 2);
	else if (type == 5)
		ft_putstr_fd("`<<'\n", 2);
	else if (type == 4)
		ft_putstr_fd("`>>'\n", 2);
	else if (type == 3)
		ft_putstr_fd("`>'\n", 2);
	else if (type == 2)
		ft_putstr_fd("`<'\n", 2);
	else if (type == 1)
		ft_putstr_fd("`|'\n", 2);
}
