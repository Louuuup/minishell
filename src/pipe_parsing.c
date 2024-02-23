#include "minishell.h"

void	ft_sglbool(bool *single, bool *dbl)
{
	if (*single == false && *dbl == false)
		*single = true;
	else if (*single == true && *dbl == false)
		*single = false;
}

void	ft_dblbool(bool *single, bool *dbl)
{
	if (*single == false && *dbl == false)
		*dbl = true;
	else if (*single == false && *dbl == true)
		*dbl = false;
}

int	ft_pipeparse(char *str)
{
	t_ibool		a;

	iboolinit(&a);
	while (ft_isspace(str[a.i]) != 0)
		a.i++;
	if (str[a.i] == '|')
		return (0);
	while (str[a.i])
	{
		if (str[a.i] == '|' && a.single == false && a.dbl == false)
		{
			a.i++;
			while (ft_isspace(str[a.i]) != 0)
				a.i++;
			if (str[a.i] == '|' || str[a.i] == '\0')
				return (0);
		}
		if (str[a.i] == '\'')
			ft_sglbool(&a.single, &a.dbl);
		if (str[a.i] == '"')
			ft_dblbool(&a.single, &a.dbl);
		a.i++;
	}
	return (1);
}

int	iboolinit(t_ibool *ibool)
{
	if (!ibool)
		return (0);
	ibool->i = 0;
	ibool->dbl = false;
	ibool->single = false;
	return (1);
}
