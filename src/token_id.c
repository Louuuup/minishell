#include "minishell.h"

int ft_idheredoc(t_idtok *id)
{
    if (id->app || id->in || id->out)
        return(0); //need to work on error message 
    id->here = true;
    return (1);
}

int ft_idinput(t_idtok *id)
{
    if (id->app || id->out || id->here)
        return(0);
    id->in = true;
     return (1);
}

int ft_idappend(t_idtok *id)
{
    if (id->in || id->out || id->here)
        return(0);
    id->app = true;
     return (1);
}

int ft_idoutput(t_idtok *id)
{
    if (id->app || id->in || id->here)
        return(0);
    id->out = true;
    return (1);
}

int ft_id_cmd_file_arg(char *str, t_idtok *id,t_data *data)
{
    t_cmd   *tmp;
    int     i;

    i = 0;
    tmp = data->cmd;
    while(tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (id->app)
    {
        tmp->outfile = str;
        tmp->out_flag = REDIR_APPEND;
        id->app = false;
    }
    else if(id->in)
    {
        tmp->infile = str;
        tmp->in_flag = REDIR_INPUT;
        id->in = false;
    }
    else if(id->out)
    {
        tmp->outfile = str;
        tmp->out_flag = REDIR_OVERWRITE;
        id->out = false;
    }
    /*else if(id->here)
    {
       handle heredoc here maybe in linked list ??
       id->here = false; 
    }*/
    else if (!id->cmd)
    {
        tmp->cmd = malloc((id->cmd_size + 1) * (sizeof(char **)));
        tmp->cmd[0] = str;
        id->cmd = true;
        return (1);
    }
    else if (id->cmd)
    {
         while(tmp->cmd[i])
            i++;
        printf("%d\n", i);
        tmp->cmd[i] = str;
         printf("%d\n", i);      
    }
    printf("%s\n", data->cmd->cmd[1]);
     return (1);
}