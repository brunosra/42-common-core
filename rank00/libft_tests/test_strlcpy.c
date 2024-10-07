#include "../libft.h"
#include <string.h>
#include <stdio.h>

int main(void)
{
	char d[10] = "12345";
	char s[10] = "67890";

	ft_strlcpy(d, s, 5);
	printf("%s\n", d);
}
