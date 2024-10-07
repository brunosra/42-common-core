#include "../libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "abcdefghijklmnopqrstuvxyzabcdefghijklmnopqrstuvxyz";

	printf("str: %p\n", str);
	printf("char: c - %s\n", ft_strchr(str, 'c'));
	printf("char: 0 - %p\n", ft_strchr(str, 0));
	printf("char: z - %s\n", ft_strchr(str, 'z'));
	printf("char: \" \" - %s\n", ft_strchr(str, ' '));

	printf("char: c - %s\n", strchr(str, 'c'));
	printf("char: 0 - %p\n", strchr(str, 0));
	printf("char: z - %s\n", strchr(str, 'z'));
	printf("char: \" \" - %s\n", strchr(str, ' '));
}
