/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:00:14 by yakary            #+#    #+#             */
/*   Updated: 2023/03/10 18:38:19 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mettons;

	mettons = ft_calloc(sizeof(t_list), 1);
	if (!mettons)
		return (NULL);
	mettons->content = content;
	mettons->next = NULL;
	return (mettons);
}
