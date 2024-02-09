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
    char **str;
    int i;
    int j;

    i = 0;
    j = 0;
    str = NULL;
    while(data->parser.cmd_list[i])
    {
        ft_cmdadd_back(&data->cmd, ft_lstnewcmd());
        str = ft_split_tok(data->parser.cmd_list[i]); //have to rework on quotes to handle
        parsing(str, data);                            //things like a"$VAR"                       
        while(str[j])
        {
            printf("tokenizer :%s\n", str[j]);
            j++;
        }
        j=0;
        i++;
        //cmd_status(data->cmd);
    }
    return (1);
    //ft_strdup() //replace with gc_strdup
}