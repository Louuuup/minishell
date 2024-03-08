/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingerror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:14:54 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:14:55 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosedqtes(t_data *data)
{
	exit_code(1);
	free(data->user_prompt);
	error_str("unclosed quote\n");
	return (0);
}

int	pipeerr(t_data *data)
{
	exit_code(1);
	free(data->user_prompt);
	error_str("syntax error with token `|'\n");
	return (0);
}
