#include "minishell.h"

void sig_inthandler(int i)
{
	if (i)
		ft_putendl_fd("\0", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
}

void sigchildint(int i)
{
	if (i)
	get_data()->code_exit = 128 + 2;
	signal(SIGINT, SIG_DFL);
}

void sigchildquit(int i)
{
	if (i)
	get_data()->code_exit = 128 + 2;
	signal(SIGQUIT, SIG_DFL);
}