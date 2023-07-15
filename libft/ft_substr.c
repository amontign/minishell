/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:01:25 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:23:07 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	get_len(char const *s, unsigned int start, size_t len);

static size_t	get_len(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	max;

	max = 0;
	s_len = ft_strlen(s);
	if (start < s_len)
		max = s_len - start;
	if (max > len)
		max = len;
	return (max);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	max;
	char	*sub;

	i = 0;
	if (!s)
		return (0);
	max = get_len(s, start, len);
	sub = (char *)malloc((max + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < max)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
