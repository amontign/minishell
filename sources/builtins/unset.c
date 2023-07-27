/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:14:23 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/27 11:00:21 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(t_data **tmp)
{
	(*tmp)->previous->next = (*tmp)->next;
	(*tmp)->next->previous = (*tmp)->previous;
	free((*tmp)->var);
	free((*tmp));
}

int	builtin_unset(t_data **data, char **to_unset)
{
	t_data	*tmp;
	int		size_str;
	int		i;
/*Si il y a un pipe avant ou apres une command unset, unset ne s'execute pas.*/

	tmp = *data;
	i = 0;
	if (!to_unset)
		return (1);
	while (tmp && to_unset[i])
	{
		size_str = ft_strlen(to_unset[i]);
		if (ft_strncmp(tmp->var, to_unset[i], (size_t)size_str) == 0)
		{
			remove_env_var(&tmp);
			i++;
			tmp = *data;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data *data;
// 	t_data	*tmp;

// 	(void)argc;
// 	data = NULL;
// 	ft_getenv(&data, envp);
// 	tmp = data;
// 	while (tmp)
// 	{
// 		ft_printf("%s\n", tmp->var);
// 		tmp = tmp->next;
// 	}
// 	builtin_unset(&data, argv + 2);
// 	tmp = data;
// 	while (tmp)
// 	{
// 		ft_printf("%s\n", tmp->var);
// 		tmp = tmp->next;
// 	}
// }