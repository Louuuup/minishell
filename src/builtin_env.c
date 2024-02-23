#include "minishell.h"

char *get_var(char **env, char *var)
{
    int i;
    int j;

    i = 0;
    if (DEBUG_ON)
        printf("(get_var) var: %s\n", var);
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        if (ft_strncmp(env[i], var, j) == 0)
            return (env[i] + j + 1);
        i++;
    }
    return (NULL);
}

char *set_var(char **env, char *var, char *value)
{
    int i;
    int j;
    char *new_var;

    i = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        if (ft_strncmp(env[i], var, j) == 0)
        {
            new_var = gc_strjoin(var, "=");
            new_var = gc_strjoin(new_var, value);
            free(env[i]);
            env[i] = new_var;
            return (env[i]);
        }
        i++;
    }
    return (NULL);
}

char **rm_var(t_data *data, char *var)
{
    int i;
    int j;
    char **new_env;

    if (!data->env || !var || !get_var(data->env, var))
        return (NULL);
    if (DEBUG_ON)
        printf("(rm_var) arr_len: %d\n", arr_len(data->env));
    new_env = gc_calloc(arr_len(data->env), sizeof(char *));
    i = 0;
    while (data->env[i])
    {
        j = 0;
        while (data->env[i][j] && data->env[i][j] != '=')
            j++;
        if (ft_strncmp(data->env[i], var, j) != 0)
        {
            if (DEBUG_ON)
                printf("(rm_var) copying %s\n", data->env[i]);
            new_env[i] = data->env[i];
            i++;
        }
        else
        {
            if (DEBUG_ON)
                printf("(rm_var) freeing %s\n", data->env[i]);
            gc_free_one(data->memblock, data->env[i]);
            i++;
        }
    }
    return (new_env);
}

char    **add_var(char **env, char *var, char *value)
{
    if (DEBUG_ON)
        printf("(add_var) var: %s, value: %s\n", var, value);
    int i;
    char **new_env;

    i = 0;
    while (env[i])
        i++;
    new_env = gc_calloc(i + 2, sizeof(char *));
    i = 0;
    while (env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = ft_strjoin(var, "=");
    new_env[i] = ft_strjoin(new_env[i], value);
    env = arr_free((void **)env);
    if (DEBUG_ON)
        printf("(add_var) new_env: %s\n", new_env[i]);
    free(env);
    env = new_env;
    return (NULL);
}

void b_env(t_cmd *cmd)
{
    int i;
    char **env;

    i = 0;
    env = get_data()->env;
    while (env[i])
    {

        if (find_symbol('=', env[i]))
        {
            ft_putstr_fd(env[i], cmd->fd_out);
            ft_putchar_fd('\n', cmd->fd_out);
        }
        i++;
    }
}