#include "minishell.h"

int b_unset(t_cmd *cmdt)
{
    int i;
    char *var;
    t_data *data;

    data = get_data();
    i = 1;
    while (cmdt->cmd[i])
    {
        var = get_var(data->env, cmdt->cmd[i]);
        if (var)
            data->env = rm_var(data, cmdt->cmd[i]);
        i++;
    }
    return (NO_ERROR);
}
