/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:15:42 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:21:55 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_src;
	char	*tmp_dest;
	size_t	i;

	tmp_src = (char *)src;
	tmp_dest = (char *)dest;
	i = n - 1;
	if (dest > src)
	{
		while ((int)i >= 0)
		{
			tmp_dest[i] = tmp_src[i];
			i--;
		}
		return (tmp_dest);
	}
	else
	{
		tmp_dest = ft_memcpy(dest, src, n);
		return (tmp_dest);
	}
	return (tmp_dest);
}
