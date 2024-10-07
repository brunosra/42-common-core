#include "../libft.h"
#include <stdio.h>

int	main(void)
{
	printf("c is %c\n", ft_toupper('c'));
	printf("* is %c\n", ft_toupper('*'));
	printf("500 is %c\n", ft_toupper(500));
	printf("0 is %c\n", ft_toupper(0));
	printf("-10 is %c\n", ft_toupper(-10));
}
