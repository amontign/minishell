/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_create_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:42:15 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/19 14:54:29 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*This function creates a new node for t_data chained list.*/

t_data	*ft_lstnew_data(char *var_env)
{
	t_data	*new;

	if (!var_env)
		return (NULL);
	new = malloc(sizeof(t_data));
	if (!new)
		return (ft_printf("minishell: malloc error\n"), NULL);
	new->var = ft_strdup(var_env);
	if (!new->var)
		return (free(new), NULL);
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

/*This function adds new nodes at the end of a t_data chained list.*/

void	ft_lstadd_back_data(t_data **data, t_data *new)
{
	t_data	*tmp;

	if ((*data))
	{
		tmp = *data;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->previous = tmp;
		tmp->next = new;
	}
	else
		*data = new;
}

/*This function frees the t_data chained list.*/

void	ft_lstclear_data(t_data **data)
{
	t_data	*tmp;

	if (!(*data) || !data)
		return ;
	while (*data)
	{
		tmp = (*data)->next;
		free((*data)->var);
		free(*data);
		*data = tmp;
	}
	*data = NULL;
}
