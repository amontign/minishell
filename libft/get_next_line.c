/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:21:57 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:36:48 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	int				reader;
	char			*buf;
	char			*line;
	char			*vide;

	if (fd < 0 || fd > RLIMIT_NOFILE || BUFFER_SIZE <= 0
		|| read(fd, &vide, 0) < 0)
		return (NULL);
	reader = 0;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (free(buf), NULL);
	if (!stash)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		buf[reader] = '\0';
		if (reader == 0 || reader == -1)
			return (free(buf), NULL);
		stash = ft_lstnew(buf);
		if (!stash)
			return (ft_lstclear(&stash), free(buf), NULL);
	}
	return (free(buf), line = read_n_stash(&stash, fd, reader));
}

char	*read_n_stash(t_list **stash, int fd, int reader)
{
	t_list	*new;
	char	*buf;
	char	*line;

	new = (*stash);
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (found_newline(new->content) == 0)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		buf[reader] = '\0';
		if (reader == 0)
			break ;
		if (reader == -1)
			return (ft_lstclear(stash), free(buf), NULL);
		new = ft_lstnew(buf);
		if (!new)
			return (ft_lstclear(stash), free(buf), NULL);
		ft_lstadd_back(stash, new);
	}
	if ((*stash)->content[0] == '\0' && (*stash)->next == NULL && reader == 0)
		return (free(buf), NULL);
	return (free(buf), line = concatenate_stash(stash));
}

char	*concatenate_stash(t_list	**stash)
{
	t_list	*tmp;
	char	*concat;
	int		size_concat;

	size_concat = 0;
	tmp = (*stash);
	while (tmp)
	{
		size_concat += found_newline_v2(tmp->content);
		tmp = tmp->next;
	}
	concat = malloc((size_concat + 1) * sizeof(char));
	if (!concat)
		return (NULL);
	tmp = (*stash);
	concatenate_stash2(tmp, concat, size_concat);
	(*stash) = create_new_n_remove_remaining(stash);
	return (concat);
}

void	concatenate_stash2(t_list	*tmp, char *concat, int size_concat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (j < (size_concat) && tmp->content[i] != '\0')
		{
			concat[j] = tmp->content[i];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	concat[j] = '\0';
}

t_list	*create_new_n_remove_remaining(t_list **stash)
{
	t_list	*remaining_chars;
	t_list	*tmp;
	int		i;

	remaining_chars = NULL;
	tmp = (*stash);
	i = 0;
	if (stash)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		while (tmp->content[i] != '\n' && tmp->content[i + 1] != '\0')
			i++;
		remaining_chars = ft_lstnew(tmp->content + (i + 1));
	}
	if (remaining_chars->content[0] == '\0')
		return (ft_lstclear(stash), ft_lstclear(&remaining_chars), NULL);
	return (ft_lstclear(stash), remaining_chars);
}
