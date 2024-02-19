#include "minishell.h"

void	ft_builtincheck(t_cmd *cmd)
{
	if ((!ft_strncmp(cmd->cmd[0], "echo", 5)) || \
	(!ft_strncmp(cmd->cmd[0], "cd", 3)) || \
	(!ft_strncmp(cmd->cmd[0], "pwd", 4)) || \
	(!ft_strncmp(cmd->cmd[0], "export", 7)) || \
	(!ft_strncmp(cmd->cmd[0], "unset", 6)) || \
	(!ft_strncmp(cmd->cmd[0], "env", 4)) || \
	(!ft_strncmp(cmd->cmd[0], "exit", 5)))
		cmd->built_in = true;
	else
		cmd->built_in = false;
}


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
        ft_expansion(str, &tmp->outfile);
        tmp->out_flag = REDIR_APPEND;
        id->app = false;
    }
    else if(id->in)
    {
        ft_expansion(str, &tmp->infile);
        tmp->in_flag = REDIR_INPUT;
        id->in = false;
    }
    else if(id->out)
    {
        ft_expansion(str, &tmp->outfile);
        tmp->outfile = str;
        tmp->out_flag = REDIR_OVERWRITE;
        id->out = false;
    }
    else if(id->here)
    {
       ft_removeqte(str);
       ft_docadd_back(tmp->doc, ft_lstnewdoc(str));
       id->here = false; 
    }
    else if (!id->cmd)
    {
        tmp->cmd = malloc((id->cmd_size + 1) * (sizeof(char *)));
        ft_expansion(str, &tmp->cmd[0]);
        ft_removeqte(tmp->cmd[0]);
        id->cmd = true;
        ft_builtincheck(tmp);
        tmp->cmd[1] = NULL;
        return (1);
    }
    else if (id->cmd)
    {
        while(tmp->cmd[i])
            i++;
        ft_expansion(str, &tmp->cmd[i]);
        ft_removeqte(tmp->cmd[i]);
        tmp->cmd[i + 1] = NULL;
        tmp->ac++;     
    }
     return (1);
}
