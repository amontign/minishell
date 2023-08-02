/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:19:50 by amontign          #+#    #+#             */
/*   Updated: 2023/08/02 20:01:13 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	equal_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_env(char **args, t_data *env, int fd)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: Bad usage\n", 2);
		ft_putstr_fd("env: usage: env\n", 2);
		return (1);
	}
	while (env)
	{
		if (equal_in_str(env->var))
		{
			ft_putstr_fd(env->var, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
	return (0);
}
