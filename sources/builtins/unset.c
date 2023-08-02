/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:14:23 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 19:59:27 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(t_data *tmp)
{
	if (tmp->next)
	{
		if (tmp->previous)
		{
			tmp->previous->next = tmp->next;
			tmp->next->previous = tmp->previous;
		}
		else
			tmp->next->previous = NULL;
		free(tmp->var);
		free(tmp);
	}
	else
	{
		if (tmp->previous)
			tmp->previous->next = NULL;
		free(tmp->var);
		free(tmp);
	}
}

int	arg_is_valid_unset(char *arg, int fd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] > 47 && arg[i] < 58)
			&& !(arg[i] > 64 && arg[i] < 91)
			&& !(arg[i] > 96 && arg[i] < 123) && arg[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", fd);
			ft_putstr_fd(arg, fd);
			ft_putstr_fd("': not a valid identifier\n", fd);
			return (0);
		}
		if (i == 0 && arg_zero_is_nb(fd, arg) == 0)
			return (0);
		i++;
	}
	return (i);
}

int	command_only2(t_cmd_tab *current)
{
	if (current->next || current->prev)
	{
		return (0);
	}
	return (1);
}

void	unset_2(t_data **data, t_data *next, t_data *tmp, char **to_unset)
{
	int	size_str;
	int	i;

	i = 1;
	while (tmp && to_unset[i])
	{
		next = tmp->next;
		size_str = ft_strlen(to_unset[i]);
		if (ft_strncmp(tmp->var, to_unset[i], (size_t)size_str) == 0)
		{
			remove_env_var(tmp);
			i++;
			if (next && !next->previous)
				*data = next;
			tmp = *data;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_data **data, char **to_unset, t_cmd_tab *current, int fd)
{
	t_data	*tmp;
	t_data	*next;
	int		i;

	tmp = *data;
	i = -1;
	next = NULL;
	while (to_unset[++i])
	{
		if (arg_is_valid_unset(to_unset[i], fd) == 0)
			return (change_status(*data, 1), 1);
	}
	if (!command_only2(current))
		return (0);
	if (!to_unset)
		return (1);
	unset_2(data, next, tmp, to_unset);
	return (0);
}
