#include "minishell.h"


int	if_builtin(t_tab_cmd *cmd_tab)
{
	if (ft_strcmp(cmd_tab->cmd, "exit") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "cd") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "env") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "unset") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "export") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "pwd") == 0)
        return (1);
    if (ft_strcmp(cmd_tab->cmd, "echo") == 0)
        return (1);
    return (0);
}