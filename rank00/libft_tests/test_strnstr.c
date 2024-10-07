#include "../libft.h"
#include <stdio.h>

int	main(void)
{
	const char	*largestring = "Foo Bar Baz";
	const char	*smallstring = "Bar";
	char *ptr;

	ptr = ft_strnstr(largestring, smallstring, 7);
	printf("%s\n", ptr ? ptr : "NULL");
}
