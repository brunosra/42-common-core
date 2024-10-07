#include "../libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "xteste";

	printf("str: %p\n", str);
	printf("char: c - %s\n", ft_strrchr(str, 'x'));
	printf("char: 0 - %p\n - %p\n", str, ft_strrchr(str, 0));
	printf("char: e - %p\n - %p\n", str, ft_strrchr(str, 'e'));
	printf("char: \" \" - %s\n", ft_strrchr(str, ' '));

	printf("char: c - %s\n", strrchr(str, 'x'));
	printf("char: 0 - %p\n - %p\n", str, strrchr(str, 0));
	printf("char: e - %p\n - %p\n", str, strrchr(str, 'e'));
	printf("char: \" \" - %s\n", strrchr(str, ' '));

}
