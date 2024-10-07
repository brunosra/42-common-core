#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libft.h"

int	main(void)
{
	char	ptr1[5];
	char	ptr2[5];
	int		i = 0;
	int		max = 5;
	char	*res1;
	char	*res2;

	res1 = memset(ptr1, 300, 10);
	res2 = ft_memset(ptr2, 300, 10);

	while (i < max)
	{
		printf("%d - 1: %d\n", i, res1[i]);
		printf("%d - 2: %d\n", i, res2[i]);
		i++;
	}
	return (0);
}
