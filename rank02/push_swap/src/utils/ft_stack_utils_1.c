/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 19:20:19 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_node	*ft_new_node(int i)
{
	t_node	*tmp_node;

	tmp_node = (t_node *) malloc(sizeof(t_node));
	if (!tmp_node)
		return (NULL);
	tmp_node->n = i;
	tmp_node->i = -1;
	tmp_node->next = NULL;
	return (tmp_node);
}

void	ft_printstack(t_stack *stack)
{
	t_node	*curr;

	ft_printf("%c: ", stack->name);
	curr = stack->head;
	while (curr != NULL)
	{
		ft_printf("<- [%d]:%d ", curr->i, curr->n);
		curr = curr->next;
	}
	ft_printf("]\n");
}

void	ft_stack_add2bottom(t_node *n, t_stack *s)
{
	t_node	*curr_node;

	curr_node = s->head;
	if (curr_node == NULL)
		s->head = n;
	else
	{
		while (curr_node->next != NULL)
			curr_node = curr_node->next;
		curr_node->next = n;
	}
	s->size++;
}

void	ft_stack_add2top(t_node *n, t_stack *s)
{
	t_node	*curr_head;

	curr_head = s->head;
	s->head = n;
	n->next = curr_head;
	s->size++;
}

void	ft_free_stack(t_stack *s)
{
	t_node	*curr_head;
	t_node	*tmp_node;

	curr_head = s->head;
	while (curr_head)
	{
		tmp_node = curr_head;
		curr_head = curr_head->next;
		free(tmp_node);
	}
	free(s);
}
