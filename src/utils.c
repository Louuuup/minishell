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

int error_out(t_data *pointer, int n)
{
	if (n == 1)
	{
		ft_putnbr_fd(STDERR_FILENO, n);
		perror("");
		pointer->code_exit = n;
	}
	return (1);
}

//checking for type ('0' for new line) for printing appropriate error
//the func to print out a message with syntax error

// void	error_in_syntax(int type, t_data *pntr)
// {
// 	pntr->code_exit = 2;
// 	ft_putchar_fd("minishell: syntax error near unexpected token ", 2);
// 	if (type == 39)
// 		ft_putchar_fd("`''\n", 2);
// 	else if (type == 0)
// 		ft_putchar_fd("`newline'\n", 2);
// 	else if (type == 34)
// 		ft_putchar_fd("`\"'\n", 2);
// 	else if (type == 5)
// 		ft_putchar_fd("`<<'\n", 2);
// 	else if (type == 4)
// 		ft_putchar_fd("`>>'\n", 2);
// 	else if (type == 3)
// 		ft_putchar_fd("`>'\n", 2);
// 	else if (type == 2)
// 		ft_putchar_fd("`<'\n", 2);
// 	else if (type == 1)
// 		ft_putchar_fd("`|'\n", 2);
// }
