#include "minishell.h"

//it sets a mode on a data structure & starts signals

void    set_mode(t_data *pntr, t_set_mode mode)
{
    pntr->mode = mode;
    start_signals(pntr);
}