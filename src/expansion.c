#include "minishell.h"

int ft_checksecexp(char *str, int pos)
{
    int     i;
    bool    single;
    bool    dbl;

    i = 0;
    single = false;
    dbl = false;
    while (i < pos)
    {
        if (str[i] == '\'')
            ft_sglbool(&single, &dbl);
        if (str[i] == '"')
            ft_dblbool(&single, &dbl);
        i++;
    }
    while(str[pos])
    {
        if(str[pos] == '$')
           while(str[pos] == '$')
            {
                pos++;
                return(pos);
            }
        pos++;
    }
    return (0);
}

int ft_expcat(t_expand *exp, char **final)
{
    t_data *data;
    int h;
    int len;

    data = get_data();
    exp->var = get_var(data->env, exp->name);
    if(exp->var)
        len = (ft_strlen(exp->str) + ft_strlen(exp->var) + 1);
    else
        len = (ft_strlen(exp->str) + 1);
    h = 0;
    exp->tmp = malloc(len + 1 * (sizeof(char)));
    while (h < exp->init)
    {
        exp->tmp[h] = exp->str[h];
        h++;
        exp->tmp[h + 1] = '\0';
    }
    if (!exp->var)
    { 
        exp->i = ft_strlen(exp->tmp);
        exp->j = (h + ft_strlen(exp->name) + 1);
        ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], ((size_t)ft_strlen(&exp->str[exp->j]) + 1));
        exp->j = h;
    }
    else if (exp->var)
    {
        ft_strlcat(&exp->tmp[h], exp->var, ((size_t)ft_strlen(exp->var) + 2));
        exp->i = ft_strlen(exp->tmp);
        exp->j = (h + ft_strlen(exp->name) + 1);
        ft_strlcat(&exp->tmp[exp->i], &exp->str[exp->j], ((size_t)ft_strlen(&exp->str[exp->j]) + 1));
    }
    if(ft_checksecexp(exp->tmp, exp->j))
        ft_expand(ft_checksecexp(exp->tmp, exp->j), exp->tmp, final);
    else
        *final = exp->tmp;
    //free(exp->name);
    if(final)
        return (0);
    return (0);
}

int ft_expand(int in, char *str, char **final)
{
    t_expand exp;
   
    exp.str = str;
    exp.i = in;
    exp.j = 0;
    exp.init = (in - 1);
    exp.name = malloc(ft_strlen(str) + 1 * sizeof(char));
    while(str[exp.i + 1] == '$')
    {
        exp.i++;
        exp.init++;
    }
    while(str[exp.i] && (ft_isalnum(str[exp.i]) || str[exp.i] == '_'))
        exp.name[exp.j++] = str[exp.i++];
    exp.name[exp.j] = '\0';
    ft_expcat(&exp, final);
    return(1);
}

int ft_expansion(char *str, char **final)
{
    int     i;
    bool    single;
    bool    dbl;

    i = 0;
    single = false;
    dbl = false;
    while (str[i])
    {
        if(str[i] == '$' && single == false)
        {
            while (str[i] == '$' && str[i])
                i++;
            return(ft_expand(i, str, final));
        }
        if (str[i] == '\'')
            ft_sglbool(&single, &dbl);
        if (str[i] == '"')
            ft_dblbool(&single, &dbl);
        i++;
    }
    *final = str;
    return (0);
}
