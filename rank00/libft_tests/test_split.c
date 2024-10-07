#include <stdio.h>
#include <stdlib.h>
#include "../libft.h"

void print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	main(void)
{
	char	**strs;
//	print_tab(ft_split("test1,test2,test3,test4,,,,,,,,", ' '));
	strs = ft_split("hello!", ' '); 
	print_tab(strs);
	free(strs);
	//print_tab(ft_split(",,,test1,,,test2,,test3,test4,,test5,,, ,,test6,,,", ','));
}
