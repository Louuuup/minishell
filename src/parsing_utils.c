#include "minishell.h"

int ft_closedquote(char *str)
{
    int     i;
    bool    single;
    bool    dbl;

    i = 0;
    single = false;
    dbl = false;
    while (str[i])
    {
        if (str[i] == '\'')
            ft_sglbool(&single, &dbl);
        if (str[i] == '"')
            ft_dblbool(&single, &dbl);
        i++;
    }
    if (single == false && dbl == false)
        return (1);
    return(0);
}

char    *ft_strtok(char *str, const char delim)
{
    static char *stock;
    char        *output;
    bool        found;

    char        quote;

    if (str)
        stock = str;
    output = 0;
    quote = 0;
    found = false;
    quote = 0;
    while (*stock)
    {
        // If we found the first quote
        if ((*stock == '"' || *stock == '\'') && quote == 0) {
            quote = *stock;
        }

        // The ending quote
        else if ((*stock == '"' || *stock == '\'') && quote == *stock) {
            quote = 0;
        }

        // Keep track of the beginning of the string inside OUTPUT
        if (!found && !(*stock == delim))
        {
            found = true;
            output = stock;
        }

        // If we found the delimiter, put a /0 at the position of the delimiter so we can send it
        else if (!quote && found && *stock == delim)
        {
            *stock = 0;
            stock++;
            break ;
        }

        // Keep going otherwise
        stock++;
    }
    return (output);
}

/*int main() {

    char arr[] = "bonjour | je suis un \"|\" | chien";

    char *temp = ft_strtok(arr, '|');
    while (temp) {
        printf("[%s]\n", temp);
        temp = ft_strtok(0, '|');
    }

    return 0;

}*/