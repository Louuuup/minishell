/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:03:19 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/19 18:20:03 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int error_out(t_data *pointer, char *str, int n)
{
	if (n == 1)
	{
		ft_putnbr_fd(2, "minishell error");
		perror("");
		pointer->code_exit = n;
	}
	return (1);
}