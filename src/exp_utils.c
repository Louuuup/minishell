/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/10 15:31:27 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	incr_symb(char *str, t_expand *exp)
{
	exp->symb = true;
	exp->name[exp->j++] = str[exp->i++];
	exp->name[exp->j] = '\0';
	return (1);
}

int	incr_exp(t_expand *exp)
{
	exp->i++;
	exp->init++;
	return (1);
}
