/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:46:22 by amontign          #+#    #+#             */
/*   Updated: 2023/08/02 09:07:39 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(char **args, int fd, t_data *env)
{
	char	*env_char;

	while (env)
	{
		if (ft_strncmp(env->var, "PWD=", 4) == 0)
		{
			env_char = ft_strdup(env->var + 4);
			break ;
		}
		env = env->next;
	}
	if (args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd(env_char, fd);
		ft_putchar_fd('\n', fd);
	}
	if (env_char)
		free(env_char);
	return (0);
}
