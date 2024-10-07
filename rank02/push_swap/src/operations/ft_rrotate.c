/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:15:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_rrotate(t_stack *stack, int s)
{
	t_node	*curr;
	t_node	*pre_last;

	if (stack->size < 2)
		return ;
	curr = stack->head;
	while (curr->next)
	{
		if (!curr->next->next)
			pre_last = curr;
		curr = curr->next;
	}
	pre_last->next = NULL;
	curr->next = stack->head;
	stack->head = curr;
	if (!s)
		ft_printf("rr%c\n", stack->name);
}

void	ft_rrotate_2(t_stack *src, t_stack *dst)
{
	ft_rrotate(src, 1);
	ft_rrotate(dst, 1);
	ft_printf("rr\n");
}
