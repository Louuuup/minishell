/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:37:33 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/17 14:31:01 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tmp_parse(t_data *data);

void	prompt_create(t_data *data)
{
	data->user_prompt = NULL;
	while (TRUE)
	{
		data->user_prompt = readline(PROMPT_NAME);
		if (data->user_prompt && !strncmp(data->user_prompt, "\0", 2))
		{
			free(data->user_prompt);
			data->user_prompt = NULL;
		}
		else
			tmp_parse(data);
	}

}

// for me, will delete once we have the real parsing
void	tmp_parse(t_data *data)
{
	if (!ft_strncmp(data->user_prompt, "cat", 3))
		printf("iscat\n");
}
