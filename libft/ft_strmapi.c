/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:26:52 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:22:45 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size_s;
	char			*mapi;

	i = 0;
	if (!s || !f)
		return (NULL);
	size_s = ft_strlen(s);
	mapi = (char *)malloc((size_s + 1) * sizeof(char));
	if (!mapi)
		return (NULL);
	while (i < size_s)
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
