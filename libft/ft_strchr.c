/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:19:20 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:22:20 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	real;

	real = (char)c;
	while (*s != '\0' || real == 0)
	{
		if (*s == real)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
