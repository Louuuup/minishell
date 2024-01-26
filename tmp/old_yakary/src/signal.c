#include "minishell.h"
#include <signal.h>

int global_signal = 0;

//the sigint_manager function is a signal handler for SIGINT that sets a global flag and performs certain actions to handle the interruption gracefully, such as printing a newline, moving to a new line, and redisplaying the command line. This allows the minishell to handle Ctrl+C interrupts in a way that is user-friendly and consistent with terminal behavior.

void    sigint_manager(int status)
{
	if (status == SIGINT)
	{
		global_signal = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//the manage_multiline function is a signal handler designed to handle SIGINT signals during multiline input. It sets a global flag, simulates the effect of pressing Enter, replaces the current input line with an empty string, and moves to a new line, providing a graceful way to handle interruptions during multiline input scenarios in the minishell.

void    manage_multiline(int status)
{
	if (status == SIGINT)
	{
		global_signal = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

//the start_signals function adapts the signal handling behavior based on the execution mode of the shell, ensuring appropriate responses to signals in different scenarios such as multiline input, child process execution, non-interactive mode, and interactive mode.

void    start_signals(t_data *pnt)
{
	if (pnt->mode == INTERACT)
	{
		signal(SIGINT, &sigint_manager);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (pnt->mode == MULTILINE)
	{
		signal(SIGINT, &manage_multiline);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (pnt->mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (pnt->mode == NON_INTERACT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

//The set_mode function provides a convenient way to update the execution mode and configure signal handlers accordingly. It encapsulates the logic of setting the mode and applying the necessary signal handling setup.

void	set_mode(t_data *pnt, t_set_mode mode)
{
	pnt->mode = mode;
	start_signals(pnt);
}
