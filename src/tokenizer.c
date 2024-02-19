#include "minishell.h"

 int id_tok(char *str, t_idtok *id, t_data *data)
 {
    if (!ft_strcmp(str, "<<"))
        ft_idheredoc(id);
    else if (!ft_strcmp(str, "<"))
        ft_idinput(id);
    else if (!ft_strcmp(str, ">>"))
        ft_idappend(id);
    else if (!ft_strcmp(str, ">"))
        ft_idoutput(id);
    else (ft_id_cmd_file_arg(str, id, data));
        return(1);
    return(0); 
 }


int parsing(char **str, t_data *data)
{
   t_idtok  id;

   id.app = false;
   id.cmd = false;
   id.out = false;
   id.here = false;
   id.in = false;
   id.i = 0;
   id.cmd_size = 0;
    while(str[id.i])
    {
        id.cmd_size++;
        id.i++;
    }
    id.i = 0;
    while(str[id.i])
    {                                     
        if(!id_tok(str[id.i], &id, data))
            return(0);                    //add error code here
        id.i++;
    }
    return(1);
}

int		tokenizer(t_data *data)
{
    int i;

    i = 0;
    while(data->parser.cmd_list[i])
    {
        ft_cmdadd_back(&data->cmd, ft_lstnewcmd());
        data->parser.sgl_cmd = ft_split_tok(data->parser.cmd_list[i]);
        data->parser.free[i] = data->parser.sgl_cmd;
        if(!parsing(data->parser.sgl_cmd, data))
            return(0);
        data->parser.free[i] = data->parser.sgl_cmd;                                               
        i++;
    }
    data->parser.free[i + 1] = NULL;
    i = 0;
    while(data->parser.sgl_cmd[i])
    {
        printf("string is%s\n",data->parser.sgl_cmd[i]);
        i++;
    }
    return (1);
}