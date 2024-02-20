#include "minishell.h"

int tok_arg(char *str, t_cmd *tmp)
{
    int     i;

    i = 0;
    while(tmp->cmd[i])
        i++;
    ft_expansion(str, &tmp->cmd[i]);
    ft_removeqte(tmp->cmd[i]);
    tmp->cmd[i + 1] = NULL;
    tmp->ac++;
    return(1);  
}