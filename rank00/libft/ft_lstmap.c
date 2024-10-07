/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <bschwell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:12:33 by bschwell          #+#    #+#             */
/*   Updated: 2024/04/23 16:42:23 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_node;
	t_list	*res_lst;
	void	*tmp_cnt;

	if (!lst || !f || !del)
		return (NULL);
	res_lst = NULL;
	while (lst)
	{
		tmp_cnt = (*f)(lst->content);
		if (tmp_cnt)
			tmp_node = ft_lstnew(tmp_cnt);
		if (tmp_node == NULL || tmp_cnt == NULL)
		{
			ft_lstclear(&res_lst, del);
			(*del)(tmp_cnt);
			return (NULL);
		}
		ft_lstadd_back(&res_lst, tmp_node);
		lst = lst->next;
	}
	return (res_lst);
}
