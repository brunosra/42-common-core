/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:14:36 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:22 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

void	ft_bring_min_top(t_stack *a)
{
	int		c;
	int		dir;

	c = ft_findpos(a, ft_min_i(a));
	dir = 0;
	if (c > (a->size / 2))
		dir = 1;
	while (ft_min_i(a) != a->head->i)
	{
		if (dir == 1)
			ft_rrotate(a, 0);
		else
			ft_rotate(a, 0);
	}
}
