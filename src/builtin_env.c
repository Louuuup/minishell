#include "minishell.h"

char *get_var(char **env, char *var)
{
    int i;
    int j;

    i = 0;
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
            new_var = ft_strjoin(var, "=");
            new_var = ft_strjoin(new_var, value);
            free(env[i]);
            env[i] = new_var;
            return (env[i]);
        }
        i++;
    }
    return (NULL);
}

char    **add_var(char **env, char *var, char *value)
{
    int i;
    char **new_env;

    i = 0;
    while (env[i])
        i++;
    new_env = ft_calloc(i + 2, sizeof(char *));
    i = 0;
    while (env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = ft_strjoin(var, "=");
   
    new_env[i] = ft_strjoin(new_env[i], value);
    free(env);
    env = new_env;
}