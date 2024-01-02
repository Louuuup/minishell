/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:58:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/01/02 16:51:47 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//function is designed to convert a string representation of a number to a long int, considering leading whitespace and sign, and it includes checks for overflow conditions.

long int to_long_int(char *s)
{
    long int    n;
    int         sgn;

    n = 0;
    sgn = 1;
    if (!s)
        return (0);
    while (*s == 32 || (*s > 8 && *s < 14))
        s++;
    if (*s == '-' || *s == '+')
        if (*s++ == '-')
            sgn *= -1;
    while (*s >= '0' && *s <= '9')
    {
        int dgt = *s - '0';
        if ((n > INT_MAX && sgn == 1) || (sgn == -1 && n > INT_MAX))
            return (9999999999);
        n = n * 10 + dgt;
        s++;
    }
    return (sgn * n);
}

// void	built_exit(t_data *pntr, t_tab_cmd *tab_cmd)
// {
// 	int	cnt;

// 	cnt = pntr->cmdt_count;
// 	exit(NO_ERROR);
// }
