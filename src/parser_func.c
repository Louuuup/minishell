#include "../include/minishell.h"

// "redirection_fill" fills the array of redirections
//in the data structure with information from the
// token array

int redirections_fill(t_data *pointer, int i, int j)
{
    int cnt;

    cnt = redirections_cnt(pointer, j);
    pointer->cmdt[i].redirections = NULL;
    pointer->cmdt[i].num_redirections = cnt;
    if (cnt <= 0)
        return (0);
    pointer->cmdt[i].redirections = ft_calloc(cnt, sizeof(t_token));
    if (!pointer->cmdt[i].redirections)
        return (error_out(pointer, 1));
    cnt = 0;
    while (pointer->count_token > j && pointer->tokens[j].type != PIPE)
    {
        if (check_if_redirection(pointer->tokens[j].type) == 0)
        {
            pointer->cmdt[i].redirections[cnt].type = pointer->tokens[j].type;
            pointer->cmdt[i].redirections[cnt].no_space = pointer->tokens[j].no_space;
            pointer->cmdt[i].redirections[cnt].value = ft_strdup(pointer->tokens[1 + i++].value);
            if (!pointer->cmdt[i].redirections[cnt++].value)
                return (error_out(pointer, 1));
        }
        j++;
    }
    return (0);
}