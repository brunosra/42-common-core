/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:30:52 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sort_3(t_stack *a)
{
	if (a->head->i == ft_min_i(a) && a->head->next->i == ft_max_i(a))
		ft_swap(a, 0);
	if (a->head->i == ft_max_i(a) && a->head->next->i == ft_min_i(a))
		ft_rotate(a, 0);
	if (a->head->i > a->head->next->i)
		ft_swap(a, 0);
	if (a->head->next->i == 0)
		ft_rotate(a, 0);
	if (a->head->next->next->i == ft_min_i(a))
		ft_rrotate(a, 0);
}

void	ft_sort_4(t_stack *a, t_stack *b)
{
	ft_bring_min_top(a);
	ft_push(a, b);
	ft_sort_3(a);
	ft_push(b, a);
}

void	ft_sort_5(t_stack *a, t_stack *b)
{
	if (a->size == 3)
		ft_sort_3(a);
	else if (a->size == 4)
		ft_sort_4(a, b);
	else
	{
		ft_bring_min_top(a);
		ft_push(a, b);
		if (!ft_check_stack(a))
			ft_bring_min_top(a);
		ft_push(a, b);
		ft_sort_3(a);
		ft_push(b, a);
		ft_push(b, a);
	}
}

static int	get_max_bits(int max_i)
{
	int	max_bits;

	max_bits = 0;
	while ((max_i >> max_bits) != 0)
		++max_bits;
	return (max_bits);
}

void	ft_radix_sort(t_stack *a, t_stack *b)
{
	int		max_i;
	int		max_bits;
	int		curr_bit;
	t_node	*curr;
	int		idx;

	max_bits = get_max_bits(a->size);
	curr_bit = 0;
	while (curr_bit < max_bits || !ft_check_stack(a))
	{
		curr = a->head;
		max_i = a->size;
		while (max_i-- > 0)
		{
			idx = curr->i;
			curr = curr->next;
			if (((idx >> curr_bit) & 1) == 0)
				ft_push(a, b);
			else
				ft_rotate(a, 0);
		}
		while (b->size > 0)
			ft_push(b, a);
		curr_bit++;
	}
}
