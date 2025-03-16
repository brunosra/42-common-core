/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tcosta-f <tcosta-f@student.42porto.com>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/27 18:24:43 by tcosta-f		  #+#	#+#			 */
/*   Updated: 2024/04/27 21:23:57 by tcosta-f		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s1, const char *set);
static int	ft_find_start(const char *s1, const char *set);
static int	ft_find_end(const char *s1, const char *set);

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !set || !ft_strlen(s1))
		return (ft_strdup(""));
	start = ft_find_start(s1, set);
	if ((int)start == -1)
		return (ft_strdup(""));
	end = ft_find_end(s1, set);
	if (!start && end == ft_strlen(s1))
		return ((char *)s1);
	str = malloc(end - start + 2 * (sizeof(char)));
	if (str == NULL)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

static int	ft_find_start(const char *s1, const char *set)
{
	int		j;
	size_t	i;

	i = 0;
	j = 0;
	while (i < ft_strlen(s1) / 2)
	{
		while (set[j])
		{
			while (s1[i] != set[j] && set[j])
			{
				if (i == ft_strlen(s1))
					return (-1);
				j++;
			}
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
			}
		}
		break ;
	}
	return (i);
}

static int	ft_find_end(const char *s1, const char *set)
{
	int		j;
	size_t	i;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (i > ft_strlen(s1) / 2)
	{
		while (set[j])
		{
			while (s1[i] != set[j] && set[j])
				j++;
			if (s1[i] == set[j] && set[j])
			{
				i--;
				j = 0;
			}
		}
		break ;
	}
	return (i);
}
