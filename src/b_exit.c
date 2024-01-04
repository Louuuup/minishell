/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:58:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/01/03 19:20:08 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function checks if a given string is a valid argument for numeric operations.
//It check that the string represents a valid number by examining its chars.

int	ok_for_numeric(char *s)
{
	while (*s == '-' || *s == '+' || *s == ' ')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}

//function is designed to convert a string representation of a number to a
//long int, considering leading whitespace and sign, and it includes checks
//for overflow conditions.

long int	to_long_int(char *s)
{
	long int	n;
	int			sgn;
	int			dgt;

	n = 0;
	sgn = 1;
	if (!s)
		return (0);
	while (*s == 32 || (*s > 8 && *s < 14))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sgn *= -1;
	while (*s >= '0' && *s <= '9')
	{
		dgt = *s - '0';
		if ((n > LONG_MAX && sgn == 1) || (sgn == -1 && n > LONG_MAX))
			return (9999999999);
		n = n * 10 + dgt;
		s++;
	}
	return (sgn * n);
}

//the function handles the exit command, allowing the user to exit the program
//with a specified exit code

void	built_exit_annex(t_data *pntr, t_tab_cmd *tab_cmd,
	long int exit_code, int cnt)
{
	if (cnt < 2)
		ft_putstr_fd("exit\n", 2);
	if (!tab_cmd || tab_cmd->num_args == 1)
	{
		total_clean(pntr);
		exit(pntr->code_exit);
	}
	exit_code = to_long_int(tab_cmd->args[1]);
	if (exit_code == 9999999999)
	{
		pntr->code_exit = 2;
		if (cnt != 1)
			return ;
		total_clean(pntr);
		exit (pntr->code_exit);
	}
	if (exit_code < 0)
		pntr->code_exit = 256 + exit_code % 256;
	else
		pntr->code_exit = exit_code % 256;
	if (cnt == 1)
	{
		total_clean(pntr);
		exit(pntr->code_exit);
	}
}

//the function handles the "exit" command in a shell program

void	built_exit(t_data *pntr, t_tab_cmd *tab_cmd)
{
	int	cnt;

	cnt = pntr->cmdt_count;
	if (!tab_cmd)
	{
		ft_putstr_fd("exit\n", 2);
		total_clean(pntr);
		exit(pntr->code_exit);
	}
	if (tab_cmd && tab_cmd->num_args > 2)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2)),
			(void)(pntr->code_exit = 1);
	if (tab_cmd && tab_cmd->num_args > 1
		&& ok_for_numeric(tab_cmd->args[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: need numeric args\n", 2);
		pntr->code_exit = 2;
		if (cnt < 2)
			exit(pntr->code_exit);
		return ;
	}
	built_exit_annex(pntr, tab_cmd, 0, cnt);
}
