/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:10:46 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 13:29:26 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//To use whenever a system_call returns an error. Usage: return (shell_error());
int	shell_error(void)
{
	perror(MINISHELL_ERR);
	return (ERROR);
}

//To use whenever we manually return an error.
//Usage: return (error_str("error message"));
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

// error str with modifier to error code
int	error_str_ret(char *str)
{
	get_data()->code_exit = 1;
	ft_putstr_fd(MINISHELL_ERR, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	return (ERROR);
}

int	error_str_code(char *err, char *str, int code)
{
	get_data()->code_exit = code;
	ft_putstr_fd(MINISHELL_ERR, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	return (ERROR);
}
