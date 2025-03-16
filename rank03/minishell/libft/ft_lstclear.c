/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 01:49:35 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/30 02:45:53 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_del;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		to_del = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = to_del;
	}
	*lst = NULL;
	return ;
}
