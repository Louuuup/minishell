#include "minishell.h"

//To use whenever a system_call returns an error. Usage: return (shell_error());
int	shell_error(void)
{
	perror(MINISHELL_ERR);
	return (ERROR);
}

//To use whenever we manually return an error. Usage: return (error_str("error message"));
int	error_str(char *str)
{
	ft_putstr_fd(MINISHELL_ERR, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	return (ERROR);
}

//Can add a filename in the error message
int	error_str_file(char *str, char *file)
{
	ft_putstr_fd(MINISHELL_ERR, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(file, STDERR_FILENO);
	return (ERROR);
}
