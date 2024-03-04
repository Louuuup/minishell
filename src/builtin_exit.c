#include "minishell.h"


void get_valid_err(int code)
{
    t_data *data;

    data = get_data();
    if (code > 255)
        data->code_exit = code % 256;
    else if (code < 0)
        data->code_exit = 256 + code;
    else
        data->code_exit = code;
}

void b_exit(t_cmd *cmd)
{
    (void)cmd;
    if (DEBUG_ON)
        printf("(b_exit) b_exit called\n");
    
    if (cmd->index != 0) // si cmd n,est pas la premiere commande
        return ;
    if (cmd->cmd[1] && cmd->cmd[2])
        get_data()->code_exit = 1;
    else if (cmd->cmd[1])
    {
        if (ft_isnumber(cmd->cmd[1]))
            get_data()->code_exit = ft_atoi(cmd->cmd[1]);
        else
        {
            ft_putstr_fd("exit: ", STDERR_FILENO);
            error_str_code(cmd->cmd[1], ": numeric argument required\n", 255);
        }
    }
    else
    {
        gc_free_all(get_data()->memblock);
        exit(get_data()->code_exit); 
    }
    get_valid_err(get_data()->code_exit);
}
