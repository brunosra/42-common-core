/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tcosta-f <tcosta-f@student.42porto.com>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/22 23:54:48 by tcosta-f		  #+#	#+#			 */
/*   Updated: 2024/04/26 19:52:07 by tcosta-f		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static char	*ft_reverse_string(char *str, int len, int sig);
static int	ft_how_big_int(long n, int sig);
static char	*ft_true_itoa(long num, char *str, int sig);

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		sig;

	num = (long)n;
	sig = 0;
	if (num < 0)
	{
		sig = 1;
		num = -num;
	}
	str = malloc(ft_how_big_int(num, sig) + 1);
	if (str == NULL)
		return (NULL);
	ft_true_itoa(num, str, sig);
	ft_reverse_string(str, ft_how_big_int(num, sig), sig);
	return (str);
}

static int	ft_how_big_int(long n, int sig)
{
	int		big;
	long	num;

	big = 1 + sig;
	num = n;
	if (num == 0)
		return (big);
	while (num > 9)
	{
		num = num / 10;
		big++;
	}
	if (num < 9)
		return (big);
	return (big);
}

static char	*ft_true_itoa(long num, char *str, int sig)
{
	int		i;
	long	res;

	i = 0;
	if (sig == 1)
		str[i++] = '-';
	while (num > 9)
	{
		res = num % 10;
		str[i] = res + '0';
		num = num / 10;
		i++;
	}
	if (num <= 9)
		str[i++] = num + '0';
	str[i] = '\0';
	return (str);
}

static char	*ft_reverse_string(char *str, int len, int sig)
{
	int		i;
	char	temp;
	int		tam;

	tam = len - 1;
	i = sig;
	while (i <= len / 2 && i < tam)
	{
		temp = str[i];
		str[i] = str[tam];
		str[tam] = temp;
		i++;
		tam--;
	}
	return (str);
}
