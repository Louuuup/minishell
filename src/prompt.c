/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:37:33 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/11/20 13:36:13 by ycyr-roy         ###   ########.fr       */
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
		{
			add_history(data->user_prompt);
			tmp_parse(data);
		}

	}

}

// for me, will delete once we have the real parsing
void	tmp_parse(t_data *data)
{
	if (!ft_strncmp(data->user_prompt, "echo 1", 6))
	{
		char *str[] = {"echo", "-nnnnn", "coucou", "allo", "sheesh", "aaaa"};
		built_echo(str, 6, STDOUT_FILENO);
	}
	else if (!ft_strncmp(data->user_prompt, "echo 2", 6))
	{
		char *str[] = {"echo", "-nnnann", "coucou", "allo", "sheesh", "aaaa"};
		built_echo(str, 6, STDOUT_FILENO);
	}
	else if (!ft_strncmp(data->user_prompt, "pwd", 3))
		build_pwd(STDERR_FILENO);
	// else if (!ft_strncmp(data->user_prompt, "echo 2", 6))
	// {
	// 	char *stre[] = {"echo", "allo", "allo"};
	// 	built_echo(stre, 3, STDOUT_FILENO);
	// }
}
