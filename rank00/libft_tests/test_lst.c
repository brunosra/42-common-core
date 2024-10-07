#include "../libft.h"
#include <stdio.h>

void	ft_printlst(t_list **lst)
{
	t_list *curr;

	curr = *lst;
	while (curr->next)
	{
		if(curr->next)
			printf("%s => ", (char *) curr->content);
		curr = curr->next;
	}
	printf("%s\n", (char *) curr->content);
}

int	main(void)
{
	t_list *lst_0, *lst_1, *lst_2, *lst_3, *lst_5;

	lst_1 = ft_lstnew("1");
	lst_2 = ft_lstnew("2");
	lst_3 = ft_lstnew("3");
	lst_0 = ft_lstnew("0");
	lst_5 = ft_lstnew("5");

	lst_1->next = lst_2;
	lst_2->next = lst_3;
	ft_lstadd_front(&lst_1, lst_0);
	ft_lstadd_back(&lst_1, lst_5);
	ft_printlst(&lst_0);
	printf("size from 0: %d\n", ft_lstsize(lst_0));
	printf("size from 3: %d\n", ft_lstsize(lst_3));
}
