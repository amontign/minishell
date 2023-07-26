/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:46:22 by amontign          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:33 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(char **args, int fd)
{
	char	buf[FILENAME_MAX];

	(void)fd;
	getcwd(buf, FILENAME_MAX);
	if (args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd\n", 2);
	}
	else
	{
		ft_putstr_fd(buf, fd);
		ft_putchar_fd('\n', fd);
	}
	return (1);
}
