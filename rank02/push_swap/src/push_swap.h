/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwell <student@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:12:13 by bschwell          #+#    #+#             */
/*   Updated: 2024/08/18 18:21:40 by bschwell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_node
{
	int				n;
	int				i;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node			*head;
	char			name;
	int				size;
}	t_stack;

/* Utils */
int		ft_free_arr(char **arr);
long	ft_atol(const char *nptr);
char	*ft_join_args(int argc, char **argv);

/* Check Arguments */
int		ft_check_args(char *arg_str);

/* Stack Utils */
t_node	*ft_new_node(int i);
void	ft_printstack(t_stack *stack);
void	ft_stack_add2bottom(t_node *n, t_stack *s);
void	ft_stack_add2top(t_node *n, t_stack *s);
void	ft_free_stack(t_stack *s);
void	ft_populate_index(t_stack *s);
int		ft_check_stack(t_stack *s);
int		ft_find_lowest(t_stack *s);
int		ft_min_i(t_stack *a);
int		ft_max_i(t_stack *a);
int		ft_findpos(t_stack *s, int n);
void	ft_bring_min_top(t_stack *a);

/* Operations */
void	ft_push(t_stack *src, t_stack *dst);
void	ft_swap(t_stack *stack, int s);
void	ft_swap_2(t_stack *src, t_stack *dst);
void	ft_rotate(t_stack *stack, int s);
void	ft_rotate_2(t_stack *src, t_stack *dst);
void	ft_rrotate(t_stack *stack, int s);
void	ft_rrotate_2(t_stack *src, t_stack *dst);

/* Sort */
void	ft_sort_3(t_stack *a);
void	ft_sort_5(t_stack *a, t_stack *b);
void	ft_radix_sort(t_stack *a, t_stack *b);

#endif // !PUSH_SWAP_H
