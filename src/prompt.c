/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:37:33 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/15 15:43:01 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_create(t_data *data)
{
	data->user_prompt = readline(PROMPT_NAME);
	// if (!data->user_prompt)
	// 	printf("no_prompt\n");
}
