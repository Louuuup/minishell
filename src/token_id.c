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
    t_cmd   *tmp;

    while(tmp->next)
        tmp = tmp->next;
    if (id->app)
    {
        tmp->cmd->outfile = str;
        tmp->cmd->out_flag = REDIR_APPEND;
        id->app = false;
    }
    else if(id->in)
    {
        tmp->cmd->infile = str;
        tmp->cmd->in_flag = REDIR_INPUT;
        id->in = false;
    }
    else if(id->out)
    {
        tmp->cmd->outfile = str;
        tmp->cmd->out_flag = REDIR_OVERWRITE;
        id->out = false;
    }
    /*else if(id->here)
    {
       handle heredoc here maybe in linked list ??
       id->here = false; 
    }*/
    else if (!id.cmd)
    {
        tmp->cmd = ft_calloc(id->cmd_size *(sizeof(char **)));
        str
    }
}