/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:20:19 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_min_i(t_stack *a)
{
	int		min;
	t_node	*curr;

	min = a->head->i;
	curr = a->head;
	while (curr != NULL)
	{
		if (min > curr->i)
			min = curr->i;
		curr = curr->next;
	}
	return (min);
}

int	ft_max_i(t_stack *a)
{
	int		max;
	t_node	*curr;

	max = a->head->i;
	curr = a->head;
	while (curr != NULL)
	{
		if (max < curr->i)
			max = curr->i;
		curr = curr->next;
	}
	return (max);
}

int	ft_check_stack(t_stack *s)
{
	t_node	*curr;

	curr = s->head;
	while (curr->next != NULL)
	{
		if (curr->n > curr->next->n)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	ft_find_lowest(t_stack *s)
{
	t_node	*curr;
	int		min;

	curr = s->head;
	min = INT_MAX;
	while (curr != NULL)
	{
		if (curr->i == -1)
			if (min > curr->n)
				min = curr->n;
		curr = curr->next;
	}
	return (min);
}

void	ft_populate_index(t_stack *s)
{
	t_node	*curr;
	int		idx;

	idx = 0;
	while (idx < s->size)
	{
		curr = s->head;
		while (curr != NULL)
		{
			if (curr->n == ft_find_lowest(s))
			{
				curr->i = idx++;
				break ;
			}
			curr = curr->next;
		}
	}
}
