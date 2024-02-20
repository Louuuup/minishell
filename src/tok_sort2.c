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

int exp_qtes_bool(char *str, t_ibool *i, int pos)
{
    i->i = 0;
    i->single = false;
    i->dbl = false;
    while (i->i < pos && str[i->i])
    {
        if (str[i->i] == '\'')
            ft_sglbool(&i->single, &i->dbl);
        if (str[i->i] == '"')
            ft_dblbool(&i->single, &i->dbl);
        i->i++;
    }
    return (1);
}