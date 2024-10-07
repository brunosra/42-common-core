#include "../libft.h"
#include <stdio.h>

int	main(void)
{
	printf("C is %c\n", ft_tolower('C'));
	printf("c is %c\n", ft_tolower('c'));
	printf("* is %c\n", ft_tolower('*'));
	printf("500 is %c\n", ft_tolower(500));
	printf("0 is %c\n", ft_tolower(0));
	printf("-10 is %c\n", ft_tolower(-10));
}
