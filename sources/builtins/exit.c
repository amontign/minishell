/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:38:26 by amontign          #+#    #+#             */
/*   Updated: 2023/07/25 13:09:27 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_exit(char *arg, int fd)
{
	int	i;

	i = 0;
	(void)fd;
	while ((arg[i] > 8 && arg[i] < 14) || arg[i] == ' ')
	{
		i++;
	}
	if (ft_strncmp(arg + i, "exit", 4) == 0)
	{
		if ((arg[i + 4] > 8 && arg[i + 4] < 14) || arg[i + 4] == ' '
			|| arg[i + 4] == 0)
			return (1);
	}
	return (0);
}
