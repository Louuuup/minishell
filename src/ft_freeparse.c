/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeparse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:24 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:14:25 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free3darray(char ***array)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data();
	if (!array)
		return (NULL);
	while (array[i])
	{
		ft_free_2darray(array[i]);
		i++;
	}
	if (array != NULL)
		gc_free_one(data->memblock, array);
	return (NULL);
}

void	*ft_free_2darray(char **array)
{
	t_data	*data;
	int		i;

	i = 0;
	data = get_data();
	if (!array)
		return (NULL);
	while (array[i])
	{
		gc_free_one(data->memblock, array[i]);
		i++;
	}
	if (array)
		gc_free_one(data->memblock, array);
	return (NULL);
}

int	ft_freeparse(t_data *data)
{
	if (data->parser.cmd_list)
		gc_free_one(data->memblock, data->parser.cmd_list);
	if (data->parser.free != NULL)
		ft_free3darray(data->parser.free);	
	ft_clearcmdlst(&data->cmd);
    return (1);
}