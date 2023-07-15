/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:00:24 by cbernaze          #+#    #+#             */
/*   Updated: 2023/05/17 15:35:51 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

static int	word_count(char	*s, char c);
static int	word_len(char *s, char c);
static char	*trim_word(char *s, char c);

static int	word_count(char	*s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	word_len(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*trim_word(char *s, char c)
{
	char	*sub_tab;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = word_len(s, c);
	sub_tab = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_tab)
		return (NULL);
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		sub_tab[j] = s[i];
		i++;
		j++;
	}
	sub_tab[j] = '\0';
	return (sub_tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (char **)malloc((word_count((char *)s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			tab[j] = trim_word((char *)(s + i), c);
			i++;
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab[j] = 0;
	return (tab);
}
