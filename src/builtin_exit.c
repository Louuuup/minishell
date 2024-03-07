#include "minishell.h"

static void get_valid_err(int code)
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

void exit_code(int code)
{
    t_data *data;

    data = get_data();
    if (DEBUG_ON)
        printf("(exit_code) new code: %d\n", code);
    data->code_exit = code;
}

void b_exit(t_cmd *cmd)
{
    char *tmp;

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
            tmp = gc_strjoin("exit: ", cmd->cmd[1]);
            error_str_code(tmp, ": numeric argument required\n", 255);
            gc_free_one(get_data()->memblock, tmp);
        }
    }
    get_valid_err(get_data()->code_exit);
    write(1, "exit\n", 5);
    gc_free_all(get_data()->memblock);
    exit(get_data()->code_exit); 
}
