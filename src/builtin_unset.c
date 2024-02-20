#include "minishell.h"

void    b_unset(t_cmd *cmd)
{
    t_cmd *tmp;
    t_cmd *prev;
    t_data *data;

    data = get_data();
    tmp = data->env;
    prev = NULL;
    while (tmp)
    {
        if (!ft_strncmp(tmp->cmd[0], cmd->cmd[1], ft_strlen(cmd->cmd[1])))
        {
            if (prev)
                prev->next = tmp->next;
            else
                data->env = tmp->next;
            gc_free_one(data->memblock, tmp->cmd);
            gc_free_one(data->memblock, tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
