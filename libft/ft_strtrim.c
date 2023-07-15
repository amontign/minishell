/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:02:06 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:40:28 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		is_set(char	const *set, char c);
static size_t	is_start(char const *s1, char const *set);
static size_t	is_end(char const *s1, char const *set);

static int	is_set(char	const *set, char c)
{
	size_t	i;
	size_t	size_set;

	i = 0;
	size_set = ft_strlen_libft(set);
	while (i < size_set)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	is_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen_libft(s1) && is_set(set, s1[i]) == 1)
		i++;
	return (i);
}

static size_t	is_end(char const *s1, char const *set)
{
	size_t	size_s1;

	size_s1 = ft_strlen_libft(s1);
	while (size_s1 > 0 && is_set(set, s1[size_s1 - 1]) == 1)
		size_s1--;
	return (size_s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	*trim;

	i = 0;
	end = is_end(s1, set);
	start = is_start(s1, set);
	if (!s1 || !set)
		return (NULL);
	if (start < end)
		trim = (char *)malloc(((end - start) + 1) * sizeof(*s1));
	else
	{
		trim = (char *)malloc(1);
		trim[i] = 0;
		return (trim);
	}
	if (!trim)
		return (NULL);
	while (start != end)
		trim[i++] = s1[start++];
	trim[i] = '\0';
	return (trim);
}
