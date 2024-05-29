/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:32:30 by njackson          #+#    #+#             */
/*   Updated: 2024/03/18 16:11:04 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstmap_clear(
		t_list *lst, void *content, void (*del)(void *))
{
	if (content)
		(*del)(content);
	ft_lstclear(&lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*out;
	t_list	*out_last;
	void	*next_content;

	if (!lst || !f || !del)
		return (0);
	next_content = (*f)(lst->content);
	out = ft_lstnew(next_content);
	if (!out || !next_content)
		return (ft_lstmap_clear(out, next_content, del));
	out_last = out;
	lst = lst->next;
	while (lst)
	{
		next_content = (*f)(lst->content);
		out_last->next = ft_lstnew(next_content);
		if (!out_last->next || !next_content)
			return (ft_lstmap_clear(out, next_content, del));
		out_last = out_last->next;
		lst = lst->next;
	}
	return (out);
}
