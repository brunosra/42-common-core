#include "../libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("abc | ab | 2 : %d\n", ft_strncmp("abc", "ab", 2));
	printf("ab | abc | 2 : %d\n", ft_strncmp("ab", "abc", 2));
	printf("abc | ab | 3 : %d\n", ft_strncmp("abc", "ab", 3));
	printf("ab | abc | 3 : %d\n", ft_strncmp("ab", "abc", 3));	
	printf("ab | ab | 2 : %d\n", ft_strncmp("ab", "ab", 2));
	printf("ab | ab | 3 : %d\n", ft_strncmp("ab", "ab", 3));
	printf("abc | ab | 0 : %d\n", ft_strncmp("abc", "ab", 0));
	printf("==========\n");	
	printf("abc | ab | 2 : %d\n", strncmp("abc", "ab", 2));
	printf("ab | abc | 2 : %d\n", strncmp("ab", "abc", 2));
	printf("abc | ab | 3 : %d\n", strncmp("abc", "ab", 3));
	printf("ab | abc | 3 : %d\n", strncmp("ab", "abc", 3));	
	printf("ab | ab | 2 : %d\n", strncmp("ab", "ab", 2));
	printf("ab | ab | 3 : %d\n", strncmp("ab", "ab", 3));
	printf("abc | ab | 0 : %d\n", strncmp("abc", "ab", 0));	
}
