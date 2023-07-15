/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:50:45 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:19:33 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

static char		*copy_nb(char *s, int n, int *i);
static char		*neg_max(char *s, int n, int *i);
static size_t	len_nbr(long nbr);

static char	*neg_max(char *s, int n, int *i)
{
	int	j;

	j = *i;
	s[j] = '-';
	j++;
	copy_nb(s, ((n + 1) * -1), &j);
	*i = j;
	s[j] = '8';
	return (s);
}

static size_t	len_nbr(long nbr)
{
	size_t	len;

	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= 0 && nbr <= 9)
		return (1);
	else
	{
		while (nbr > 9)
		{
			nbr /= 10;
			len++;
		}
		return (len + 1);
	}
}

static char	*copy_nb(char *s, int n, int *i)
{
	int	j;

	j = *i;
	if (n == -2147483648)
	{
		neg_max(s, n, i);
		return (s);
	}
	if (n < 0 && n != -2147483648)
	{
		s[j] = '-';
		n *= -1;
		j++;
	}
	if (n >= 0 && n <= 9)
		s[j] = (n + '0');
	if (n > 9)
	{
		copy_nb(s, n / 10, &j);
		j++;
		copy_nb(s, n % 10, &j);
	}
	*i = j;
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;
	int		i;

	i = 0;
	len = len_nbr(n);
	if (n < 0)
		s = (char *)malloc((len + 2) * sizeof(char));
	else
		s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	copy_nb(s, n, &i);
	s[i + 1] = '\0';
	return (s);
}
