/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 14:58:50 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_inthandler(int i)
{
	if (i)
	{
		exit_code(1);
		ft_putendl_fd("\0", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigchildint(int i)
{
	if (i)
		exit_code(128 + SIGINT);
	signal(SIGINT, SIG_DFL);
}

void	sigchildquit(int i)
{
	if (i)
		exit_code(128 + SIGQUIT);
	signal(SIGQUIT, SIG_DFL);
}

void	sigcdocint(int i)
{
	if (i)
	{
		printf("SIGINT received, breaking out of the loop\n");
	}
}
