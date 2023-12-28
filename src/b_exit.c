/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkramer <mkramer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:58:13 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/12/28 16:31:43 by mkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_exit(t_data *pntr, t_tab_cmd *cmd_tab)
{
	int	cnt;

	cnt = pntr->cmdt_count;
	exit(NO_ERROR);
}
