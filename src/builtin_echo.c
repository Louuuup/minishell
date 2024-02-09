#include "minishell.h"

void    b_echo(t_cmd *cmd)
{
    int i;

    i = 1;
    while (cmd->cmd[i])
    {
        ft_putstr_fd(cmd->cmd[i], cmd->fd_out);
        if (cmd->cmd[i + 1])
            ft_putchar_fd(' ', cmd->fd_out);
        i++;
    }
    ft_putchar_fd('\n', cmd->fd_out);
}