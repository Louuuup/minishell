#include "minishell.h"

int global_signal = 0;

//it manages SIGINT with help of a global variable & inputs/outputs

void    manage_multiline(int status)
{
    if (status == SIGINT)
    {
        global_signal = 1;
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        // rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

//it starts signal functions with the mode from the data structure

void    start_signals(t_data *pntr)
{
    if (pntr->mode == MULTILINE)
    {
        signal(SIGINT, &manage_multiline);
    }
}

//it sets a mode on a data structure & starts signals

void    set_mode(t_data *pntr, t_set_mode mode)
{
    pntr->mode = mode;
    start_signals(pntr);
}