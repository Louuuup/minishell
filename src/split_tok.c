/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:15:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2024/03/08 12:15:18 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_makerq(char *s, size_t len)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = *s;
		s++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**splitterq(char **split, char *s, size_t count)
{
	t_countok	tok;

	tok.i = 0;
	tok.j = 0;
	tok.count = 0;
	while (tok.count < count)
	{
		while (s[tok.i])
		{
			while (ft_isspace(s[tok.i]))
				tok.i++;
			ft_splt_wrd_qte(&tok, s);
			split[tok.count] = word_makerq(&s[tok.i], (tok.j));
			break ;
		}
		tok.i = tok.i + tok.j;
		tok.j = 0;
		tok.count++;
	}
	split[tok.count] = NULL;
	return (split);
}

char	**ft_split_tok(char *s)
{
	char	**split;
	size_t	count;

	if (!s)
		return (NULL);
	count = word_countq(s);
	if (count == 0 || ft_strlen(s) == 0)
	{
		split = (char **)malloc(sizeof(char *));
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = (char **)gc_malloc((count + 1) * (sizeof(char *)));
	if (!split)
		return (NULL);
	split = splitterq(split, s, count);
	return (split);
}
