/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycyr-roy <ycyr-roy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:13:17 by ycyr-roy          #+#    #+#             */
/*   Updated: 2023/03/13 14:44:05 by ycyr-roy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*t_new;

	if (!lst || !f || !del)
		return (0);
	new = ft_lstnew(NULL);
	t_new = new;
	tmp = lst;
	while (tmp)
	{
		t_new->content = f(tmp->content);
		tmp = tmp->next;
		ft_lstadd_back(&new, (ft_lstnew(NULL)));
		t_new = t_new->next;
	}
	return (new);
}
