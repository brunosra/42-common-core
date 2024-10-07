#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../libft.h"

int	main(void)
{
	char	ptr1[100];
	char	ptr2[100];
	int		i = 0;
	int		max = 100;
	char	*res1;
	char	*res2;

	res1 = memset(ptr1, 42, 100);
	res2 = ft_memset(ptr2, 42, 100);

	while (i < max)
	{
		printf("%d - 1: %d\n", i, res1[i]);
		printf("%d - 2: %d\n", i, res2[i]);
		i++;
	}
	bzero(ptr1, 100);
	ft_bzero(ptr2, 100);
	i = 0;

	while (i < max)
	{
		printf("%d - 1: %d\n", i, res1[i]);
		printf("%d - 2: %d\n", i, res2[i]);
		i++;
	}

	return (0);
}
