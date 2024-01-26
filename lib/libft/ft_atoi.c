/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakary <yakary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:33:07 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/03/14 15:19:39 by yakary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	atoi_nbr(const char *str)
{
	int		n;
	char	*string;

	n = 0;
	string = (char *)str;
	while (*string >= 48 && *string <= 57)
	{
		n *= 10;
		n += (*string - 48);
		string++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	int		neg;
	char	*string;

	string = (char *)str;
	neg = 1;
	if (*string == '\0')
		return (0);
	while (*string == 32 || (*string >= 9 && *string <= 13))
	{
		string++;
	}
	if (*string == 43)
		string++;
	else if (*string == 45)
	{
		neg = -neg;
		string++;
	}
	return (atoi_nbr(string) * neg);
}
