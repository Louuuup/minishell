#include "minishell.h"

void    b_cd(t_cmd *cmd)
{
    char *oldpwd;
    char *pwd;

    pwd = NULL;
    oldpwd = get_var(get_data()->env, "PWD");
    if (cmd->ac > 1)
    {
        pwd = gc_strjoin(pwd, cmd->cmd[1]);
        pwd = gc_strjoin(oldpwd, "/");
    }
    else
        pwd = get_var(get_data()->env, "HOME");
    if (access(pwd, F_OK) != ERROR)
    {
        if (chdir(pwd) == ERROR)
            error_str("cd: error");
    }
    else
        error_str("cd: no such file or directory");
}

void    b_pwd(t_cmd *cmd)
{
    ft_putstr_fd(get_var(get_data()->env, "PWD"), cmd->fd_out);
    ft_putchar_fd('\n', cmd->fd_out);
}