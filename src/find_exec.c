#include "minishell.h"

//is responsible for locating an executable binary in the system
//and determining whether it is available for execution (127 - command not found)

int find_exec(t_data *pntr, t_tab_cmd *cmd_tab)
{
    int i;
    int result;

    i = -1;
    if (!cmd_tab->cmd)
        return (1);
    if (cmd_tab->cmd[0] == '\0')
    {
        ft_putstr_fd("minishell: command not found\n", 2);
        pntr->code_exit = 127;
        return (1);
    }
    if (ft_strchr(cmd_tab->cmd, '/') != 0 || cmd_tab->cmd[0] == '.')
        return ("LATER!!!");
    
    return (1);
}