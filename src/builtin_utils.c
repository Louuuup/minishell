#include "minishell.h"

int export_valid(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return(FALSE);
		i++;
	}
	return (TRUE);
}

char *var_name(char *str)
{
    int i;
    char *new_str;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    new_str = ft_substr(str, 0, i);
    if (DEBUG_ON)
        printf("(var_name) found %s in %s\n", new_str, str);
    return (str);
}