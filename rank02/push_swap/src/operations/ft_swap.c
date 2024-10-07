/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:15:37 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_swap(t_stack *stack, int s)
{
	t_node	*tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->head;
	stack->head = stack->head->next;
	tmp->next = tmp->next->next;
	stack->head->next = tmp;
	if (!s)
		ft_printf("s%c\n", stack->name);
}

void	ft_swap_2(t_stack *src, t_stack *dst)
{
	ft_swap(src, 1);
	ft_swap(dst, 1);
	ft_printf("ss\n");
}
