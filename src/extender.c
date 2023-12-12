#include "../include/minishell.h"

//auxiliary func, works like strchr

int if_has(const char *n, char c)
{
	if (!n)
		return (0);
	while (*n)
	{   if (*n == c)
			return (1);
	}
	return (0);
}

//what if we have "$" or "?" inside of a token? we need replace key with exception
//the func extends tokens after checking variables

int extender(t_data *pntr)
{
	int exception;
	int stop;
	int i;

	stop = pntr->count_token;
	i = 0;
	while (i < stop)
	{
		if (pntr->tokens[i].type == REDIRECT_MULTILINE)
		{
			i += 2;
			while (pntr->tokens[i].no_space)
				i++;
		}
		if (if_has(pntr->tokens[i].value, '$') && (pntr->tokens[i].type == DQUOTE || pntr->tokens[i].type == WORD))
		{

		}
		i++;
	}
	return (0);
}