#include "minishell.h"

void	ft_strtokut(t_strtok *tok, char *stock)
{
	tok->found = true;
	tok->output = stock;
}

void	ft_strtokinit(t_strtok *tok)
{
	tok->found = false;
	tok->output = 0;
	tok->quote = 0;
}

size_t	ft_cmdcount(char *str)
{
	int		i;
	size_t	count;
	bool	single;
	bool	dbl;

	i = 0;
	count = 0;
	single = false;
	dbl = false;
	while (str[i])
	{
		if (str[i] == '|' && single == false && dbl == false)
			count++;
		if (str[i] == '\'')
			ft_sglbool(&single, &dbl);
		if (str[i] == '"')
			ft_dblbool(&single, &dbl);
		i++;
	}
	return (count);
}

int	ft_closedquote(char *str)
{
	int		i;
	bool	single;
	bool	dbl;

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
	return (0);
}

char	*ft_strtok(char *str, const char delim)
{
	static char	*stock;
	t_strtok	tok;

	if (str)
		stock = str;
	ft_strtokinit(&tok);
	while (*stock)
	{
		if ((*stock == '"' || *stock == '\'') && tok.quote == 0)
			tok.quote = *stock;
		else if ((*stock == '"' || *stock == '\'') && tok.quote == *stock)
			tok.quote = 0;
		if (!tok.found && !(*stock == delim))
			ft_strtokut(&tok, stock);
		else if (!tok.quote && tok.found && *stock == delim)
		{
			*stock = 0;
			stock++;
			break ;
		}
		stock++;
	}
	return (tok.output);
}
