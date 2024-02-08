#include "minishell.h"

int ft_idheredoc(t_idtok *id)
{
    if (id->app || id->in || id->out)
        return(0); //need to work on error message 
    id->here = true;
}

int ft_idinput(t_idtok *id)
{
    if (id->app || id->out || id->here)
        return(0);
    id->in = true;
}

int ft_idappend(t_idtok *id)
{
    if (id->in || id->out || id->here)
        return(0);
    id->app = true;
}

int ft_idoutput(t_idtok *id)
{
    if (id->app || id->in || id->here)
        return(0);
    id->out = true;
}

int ft_id_cmd_file_arg(char *str, t_idtok *id,t_data *data)
{
    if (id->app)
    
    else if(id->in)
    else if(id->out)
    else if(id->here)
}