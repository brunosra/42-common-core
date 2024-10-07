#include "../libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "abcdefghijklmnopqrstuvxyzabcdefghijklmnopqrstuvxyz";

	printf("str: %p\n", str);
	printf("char: c - %s\n", (char *) ft_memchr(str, 'c', 30));
	printf("char: 0 - %p\n", (char *) ft_memchr(str, 0, 30));
	printf("char: z - %s\n", (char *) ft_memchr(str, 'z', 30));
	printf("char: \" \" - %s\n", (char *) ft_memchr(str, ' ', 30));

	printf("char: c - %s\n", (char *) memchr(str, 'c', 30));
	printf("char: 0 - %p\n", (char *) memchr(str, 0, 30));
	printf("char: z - %s\n", (char *) memchr(str, 'z', 30));
	printf("char: \" \" - %s\n", (char *) memchr(str, ' ', 30));
}
