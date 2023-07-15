/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:05:22 by amontign          #+#    #+#             */
/*   Updated: 2023/07/15 15:33:15 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_struct_iter(t_cmd_tab *lst, void (*f)(void *))
{
	while (lst)
	{
		(f)(lst);
		lst = lst->next;
	}
}

t_cmd_tab	*cmd_struct_new(char **args, void *content2, int id)
{
	t_cmd_tab	*new;

	new = malloc(sizeof(t_cmd_tab));
	if (!new)
		return (NULL);
	new->args = args;
	new->cmd_name = content2;
	new->id = id;
	new->path = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->errfile = NULL;
	new->next = NULL;
	return (new);
}

t_cmd_tab	*cmd_struct_last(t_cmd_tab *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_struct_add_back(t_cmd_tab **lst, t_cmd_tab *new)
{
	t_cmd_tab	*last;
	t_cmd_tab	*new_last;

	if (*lst)
	{
		last = cmd_struct_last(*lst);
		last->next = new;
		new_last = last->next;
		new_last->prev = last;
	}
	else
	{
		*lst = new;
	}
}