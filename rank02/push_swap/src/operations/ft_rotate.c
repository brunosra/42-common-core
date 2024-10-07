/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:15:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_rotate(t_stack *stack, int s)
{
	t_node	*tmp;
	t_node	*last;

	if (stack->size < 2)
		return ;
	tmp = stack->head;
	stack->head = stack->head->next;
	last = stack->head;
	while (last->next)
		last = last->next;
	last->next = tmp;
	tmp->next = NULL;
	if (!s)
		ft_printf("r%c\n", stack->name);
}

void	ft_rotate_2(t_stack *src, t_stack *dst)
{
	ft_rotate(src, 1);
	ft_rotate(dst, 1);
	ft_printf("rr\n");
}
