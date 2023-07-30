/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:14:23 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/30 11:59:32 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(t_data **head, t_data *tmp)
{
	if (tmp->next)
	{
		if (tmp->previous)
		{
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;
		}
		else
		{
			*head = tmp->next;
			tmp->next->previous = NULL;
		}
	}
	else if (tmp->previous)
	{
		tmp->previous->next = NULL;
	}
	else
	{
		*head = NULL;
	}
	free(tmp->var);
	free(tmp);
}

int	command_only2(t_cmd_tab *current)
{
	if (current->next || current->prev)
	{
		return (0);
	}
	return (1);
}

int	builtin_unset(t_data **data, char **to_unset, t_cmd_tab *current)
{
	t_data	*tmp;
	t_data	*next;
	int		size_str;
	int		i;

	tmp = *data;
	i = 1;
	if (!command_only2(current))
		return (0);
	if (!to_unset)
		return (1);
	while (tmp && to_unset[i])
	{
		next = tmp->next;
		size_str = ft_strlen(to_unset[i]);
		if (ft_strncmp(tmp->var, to_unset[i], (size_t)size_str) == 0)
		{
			remove_env_var(data, tmp);
			i++;
		}
		tmp = next;
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