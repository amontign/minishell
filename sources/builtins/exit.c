/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:38:26 by amontign          #+#    #+#             */
/*   Updated: 2023/08/02 20:00:10 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_only_e(t_cmd_tab *current)
{
	if (current->next || current->prev)
	{
		return (0);
	}
	return (1);
}

int	is_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return(1);
}

int	builtin_exit(char **args, t_norm_exec *normy, t_cmd_tab *current)
{
	int	ret;
	int	quit;

	ret = 0;
	quit = 0;
	if (!args[1])
	{
		ret = normy->status;
		quit = 1;
	}
	else if (!is_nbr(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		quit = 1;
		ret = 2;
	}
	else if (args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ret = 1;
	}
	else
	{
		if (command_only_e(current))
			normy->exit = ft_atoi(args[1]) % 256;
		ret = ft_atoi(args[1]) % 256;
	}
	if (!command_only_e(current))
		return (ret);
	else if (quit)
		normy->exit = ret;
	return (ret);
}
