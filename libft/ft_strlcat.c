/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:52:07 by cbernaze          #+#    #+#             */
/*   Updated: 2023/06/26 09:03:49 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		dst_len = dstsize;
	if (dst_len < (dstsize - 1) && dstsize > 0)
	{
		while (dst[i] != '\0')
			i++;
		while (src[j] && (dst_len + j) < (dstsize - 1))
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = 0;
	}
	return (dst_len + src_len);
}
