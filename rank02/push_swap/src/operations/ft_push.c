/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:15:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_push(t_stack *src, t_stack *dst)
{
	t_node	*tmp;

	if (!(src)->head)
		return ;
	tmp = (src)->head;
	(src)->head = tmp->next;
	tmp->next = (dst)->head;
	(dst)->head = tmp;
	(dst)->size++;
	(src)->size--;
	ft_printf("p%c\n", (dst)->name);
}
