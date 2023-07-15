/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:02:16 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:22:59 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		n;
	char	real;

	n = ft_strlen(s);
	real = (char)c;
	while (n >= 0)
	{
		if (s[n] == real)
			return ((char *)(s + n));
		n--;
	}
	return (0);
}
