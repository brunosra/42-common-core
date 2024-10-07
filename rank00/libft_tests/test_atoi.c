#include "../../../42/libft/libft.h"
#include <stdio.h>
#include <limits.h>

int	main(int argc, char **argv)
{
	char	*s;

	if (argc > 1)
		s = argv[1];
	else
		s = "";

	printf("%d\n", ft_atoi(s));
}
