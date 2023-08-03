/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 08:59:08 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 08:59:41 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Attribue a un maillon l'index correspondant a sa position
dans une liste de type t_parsing*/

void	set_index(t_parsing **lexing)
{
	t_parsing	*tmp;
	int			i;

	i = 0;
	tmp = *lexing;
	while (tmp)
	{
		tmp->index = ++i;
		tmp = tmp->next;
	}
}

void	ft_lstadd_at_id(t_parsing **lexing, t_parsing *new, int index)
{
	t_parsing	*tmp;

	tmp = *lexing;
	while (tmp->index != index)
		tmp = tmp->next;
	tmp->next = new;
}
