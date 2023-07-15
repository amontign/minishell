/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:30:38 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:36:56 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	found_newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

int	found_newline_v2(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst && lst)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}

t_list	*ft_lstnew(char *str)
{
	t_list	*new;
	int		size_str;
	int		i;

	size_str = 0;
	i = -1;
	if (!str)
		return (NULL);
	while (str[size_str])
		size_str++;
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (ft_lstclear(&new), NULL);
	new->content = malloc((size_str + 1) * sizeof(char));
	if (new->content == NULL)
		return (ft_lstclear(&new), NULL);
	while (++i < size_str)
		new->content[i] = str[i];
	new->content[i] = '\0';
	new->next = NULL;
	return (new);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if ((*lst) == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		(*lst) = tmp;
	}
	*lst = NULL;
}
