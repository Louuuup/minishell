/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:22:23 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/12/06 15:38:23 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	index_sort(char **arr, int str_count, int *index)
{
	int		i;
	int		swapped;
	int		tmp;

	i = -1;
	swapped = 1;
	while (++i < str_count)
        index[i] = i;
	i = 0;
	while (arr[index[i]] && swapped)
	{
		swapped = 0;
		i = 0;
		while (i < str_count - 1)
		{
			// printf("i is %d\nstr is %s\n", i, arr[index[i]]);
			if (ft_strncmp(arr[index[i]], arr[index[i + 1]], ft_strlen(arr[index[i]])) > 0)
			{
				tmp = index[i];
				index[i] = index[i + 1];
				index[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

void	print_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (find_symbol('=', env[i]))
		{
			ft_putstr_fd(env[i], fd);
			write(fd, "\n", 1);
		}
		i++;
	}
}

void	print_export(char **env, int fd)
{
	int	i;
	int	j;
	int	equal;
	int	index[arr_len(env)];

	(void)index;
	i = 0;
	printf("str_count = %d\n", arr_len(env));
	index_sort(env, arr_len(env), index);
	while (env[i] != NULL)
	{
		j = 0;
		ft_putstr_fd(EXPORT_PREFIX, fd);
		equal = find_symbol('=', env[i]);
		while (env[index[i]][j] != '\0')
		{
			ft_putchar_fd(env[index[i]][j], fd);
			if (j > 0 && j == equal)
				ft_putchar_fd('"', fd);
			j++;
		}
		if (equal)
			ft_putchar_fd('"', fd);
		write(fd, "\n", 1);
		i++;
	}
}

void built_env(t_data *data, int fd_out)
{
	print_env(data->env, fd_out);
}
