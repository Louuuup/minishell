#include "minishell.h"

int ft_sgltok(t_countok *tok, char *str)
{   
    tok->j++;
    while(str[tok->i + tok->j] && str[tok->i + tok->j] != '\'')
        tok->j++;
    tok->j++;
    return(1);
}   
int ft_dbltok(t_countok *tok, char *str)
{   
    tok->j++;
    while(str[tok->i + tok->j] && str[tok->i + tok->j] != '\"')
            tok->j++;
	tok->j++;
    return(1);
}
int ft_outtok(t_countok *tok, char *str)
{
    tok->j++;
    if(str[tok->i + tok->j] == '>')
        tok->j++;
     return(1);
}
int ft_intok(t_countok *tok, char *str)
{
    tok->j++;
    if(str[tok->i + tok->j] == '<')
        tok->j++;
    return(1);
}
int ft_wordtok(t_countok *tok, char *str)
{
    while((!ft_isspace(str[tok->i + tok->j])) && str[tok->i + tok->j] !='\"' &&\
            str[tok->i + tok->j] !='\'' && str[tok->i + tok->j] !='<' &&\
                str[tok->i + tok->j] !='>' && str[tok->i + tok->j])
            tok->j++;
    if(str[tok->i + tok->j] == '<' || str[tok->i + tok->j] == '>')
        return (1);
     if(str[tok->i + tok->j] =='\'')
    {
        tok->j++;
        while(str[tok->i + tok->j] !='\'')
            tok->j++;
        tok->j++;
    }
    if(str[tok->i + tok->j] =='\"')
    {   
        tok->j++;
        while(str[tok->i + tok->j] !='\"')
            tok->j++;
        tok->j++;
    }
    if(str[tok->i + tok->j] && !ft_isspace(str[tok->i + tok->j]))
        ft_wordtok(tok, str);
    return(1);
}