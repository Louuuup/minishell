#include "minishell.h"

void sig_inthandler(int i)
{
	if (i)
		ft_putendl_fd("\0", 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
}