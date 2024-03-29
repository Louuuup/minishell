/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:10 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:10 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sglboolqte(bool *single, bool *dbl, t_countok *tmp)
{
	if (*single == false && *dbl == false)
	{
		*single = true;
		tmp->onqtes = true;
	}
	else if (*single == true && *dbl == false)
	{
		*single = false;
		tmp->onqtes = true;
	}
}

void	ft_dblboolqte(bool *single, bool *dbl, t_countok *tmp)
{
	if (*single == false && *dbl == false)
	{
		tmp->onqtes = true;
		*dbl = true;
	}
	else if (*single == false && *dbl == true)
	{
		tmp->onqtes = true;
		*dbl = false;
	}
}

void	inittmp(t_countok *tmp, char *str)
{
	if (tmp)
	{
		tmp->i = 0;
		tmp->j = 0;
		tmp->onqtes = false;
		tmp->tmp = malloc((ft_strlen(str) + 1) * sizeof(char));
	}
}

int	ft_removeqte(char *str)
{
	t_countok	tmp;
	bool		single;
	bool		dbl;

	single = false;
	dbl = false;
	inittmp(&tmp, str);
	while (str[tmp.i])
	{
		tmp.onqtes = false;
		if (str[tmp.i] == '\'')
			ft_sglboolqte(&single, &dbl, &tmp);
		if (str[tmp.i] == '"')
			ft_dblboolqte(&single, &dbl, &tmp);
		if (!tmp.onqtes)
			tmp.tmp[tmp.j++] = str[tmp.i++];
		else
			tmp.i++;
	}
	tmp.tmp[tmp.j++] = '\0';
	ft_strlcpy(str, tmp.tmp, (ft_strlen(tmp.tmp) + 1));
	free(tmp.tmp);
	return (0);
}
