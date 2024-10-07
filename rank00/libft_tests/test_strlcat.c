#include "../libft.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
	char d[10] = "12345";
	char *s = "67890";

	ft_strlcat(d, s, 4);
	printf("%s\n", d);
}
