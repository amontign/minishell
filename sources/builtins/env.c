/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:19:50 by amontign          #+#    #+#             */
/*   Updated: 2023/07/27 10:59:30 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(char **args, t_data *env, int fd)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: Bad usage", 2);
		ft_putstr_fd("env: usage: env\n", 2);
		return (1);
	}
	while (env)
	{
		ft_putstr_fd(env->var, fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (0);
}
