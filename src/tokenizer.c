#include "minishell.h"

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
       str = ft_split_tok(data->parser.cmd_list[i]);
       while(str[j])
       {
            printf("%s\n", str[j]);
            j++;
       }
        i++;
    }
    return (1);
    //ft_strdup() //replace with gc_strdup
}