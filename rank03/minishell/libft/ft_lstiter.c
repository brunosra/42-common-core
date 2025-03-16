/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 02:27:04 by tcosta-f          #+#    #+#             */
/*   Updated: 2024/04/30 02:40:36 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*iteri;

	if (!lst)
		return ;
	while (lst->next)
	{
		iteri = lst->next;
		(*f)(lst->content);
		lst = iteri;
	}
	(*f)(lst->content);
	return ;
}
