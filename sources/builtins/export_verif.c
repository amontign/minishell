/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_verif.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 08:57:49 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 08:58:43 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_zero_is_nb(int fd, char *arg)
{
	if ((arg[0] > 47 && arg[0] < 58))
	{
		ft_putstr_fd("minishell: export: `", fd);
		ft_putstr_fd(arg, fd);
		ft_putstr_fd("': not a valid identifier\n", fd);
		return (0);
	}
	return (1);
}

int	arg_is_valid(char *arg, int fd)
{
	int	i;

	i = 0;
	if (arg[0] == '=' || !arg[0])
	{
		ft_putstr_fd("minishell: export: `", fd);
		ft_putstr_fd(arg, fd);
		ft_putstr_fd("': not a valid identifier\n", fd);
		return (0);
	}
	while (arg[i] != '=' && arg[i])
	{
		if (!(arg[i] > 47 && arg[i] < 58) && !(arg[i] > 64 && arg[i] < 91)
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
