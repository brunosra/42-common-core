/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 09:16:55 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:06 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_findpos(t_stack *s, int n)
{
	int		c;
	t_node	*curr;

	c = 0;
	curr = s->head;
	while (curr != NULL)
	{
		c++;
		if (curr->i == n)
			break ;
		curr = curr->next;
	}
	return (c);
}

static t_stack	*ft_create_stack(char name)
{
	t_stack	*s;

	s = (t_stack *) malloc(sizeof(t_stack));
	if (!s)
		return (NULL);
	s->name = name;
	s->size = 0;
	s->head = NULL;
	return (s);
}

static void	ft_populate_stack(char *arg_str, t_stack *s)
{
	char	**str_arr;
	char	**tmp_arr;

	str_arr = ft_split(arg_str, ' ');
	tmp_arr = str_arr;
	if (str_arr)
		while (*str_arr)
			ft_stack_add2bottom(ft_new_node(ft_atoi(*str_arr++)), s);
	ft_free_arr(tmp_arr);
	ft_populate_index(s);
}

static void	free_all(t_stack *a, t_stack *b, char *arg_str)
{
	ft_free_stack(a);
	ft_free_stack(b);
	free(arg_str);
}

int	main(int argc, char **argv)
{
	char	*arg_str;
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	arg_str = ft_join_args(argc, argv);
	if (!ft_check_args(arg_str))
	{
		free(arg_str);
		return (ft_putstr_fd("Error\n", 2));
	}
	a = ft_create_stack('a');
	b = ft_create_stack('b');
	ft_populate_stack(arg_str, a);
	if (!ft_check_stack(a))
	{
		if (a->size == 2)
			ft_printf("ra\n");
		else if (a->size <= 5)
			ft_sort_5(a, b);
		else
			ft_radix_sort(a, b);
	}
	free_all(a, b, arg_str);
}
