#include "minishell.h"

// solo : pipi error
// 2 pipe following each other error
void    ft_sglbool(bool *single, bool *dbl)
        {
            if (*single == false && *dbl == false)
                *single = true;
            else if (*single == true && *dbl == false)
                *single = false;
        }
void    ft_dblbool(bool *single,bool *dbl)
        {
            if (*single == false && *dbl == false)
                *dbl = true;
            else if (*single == false && *dbl == true)
                *dbl = false;
        }

int ft_pipeparse(char *str)
{
    int     i;
    bool    single;
    bool    dbl;

    i = 0;
    single = false;
    dbl = false;
    while(ft_isspace(str[i]) != 0)
            i++;
    if(str[i] == '|')
        return(0);
    while (str[i])
    {
        if(str[i] == '|' && single == false && dbl == false)
        {
            i++;
            while(ft_isspace(str[i]) != 0)
                i++;
            if(str[i] == '|')
                return(0);
        }
        if (str[i] == '\'')
            ft_sglbool(&single, &dbl);
        if (str[i] == '"')
            ft_dblbool(&single, &dbl);
        i++;
    }
    return (1);
}