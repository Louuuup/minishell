/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboivin <fboivin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 23:51:36 by fboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_inthandler(int i)
{
	if (i)
	{
		exit_code(1);
		ft_putendl_fd("\0", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_data()->code_exit = 130;
	}
}

void sigchildint(int i)
{
	if (i)
	exit_code(128 + SIGINT);
	signal(SIGINT, SIG_DFL);
}

void sigchildquit(int i)
{
	if (i)
	exit_code(128 + SIGQUIT);
	signal(SIGQUIT, SIG_DFL);
}

void sigcdocint(int i)
{
	if (i == SIGINT)
	{
		close(*get_data()->docfd);
		gc_free_all(get_data()->memblock);
		signal(SIGINT, SIG_DFL);
		kill(0, SIGINT);
		/*ft_putendl_fd("\0", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();*/
	}
}