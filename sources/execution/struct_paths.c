/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:15:51 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:20:41 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	path_error(t_cmd_tab *c, char *str, t_data *env)
{
	c->exec = 0;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	change_status(env, 127);
}

int	place_path(char **paths, t_cmd_tab *c, t_data *env)
{
	int		i;
	char	*path;
	char	*path2;

	while (c)
	{
		i = -1;
		while (paths && paths[++i] && !c->path && c->cmd_name)
		{
			path = ft_strjoin(paths[i], "/");
			if (!path)
				return (0);
			path2 = ft_strjoin(path, c->cmd_name);
			free(path);
			if (!path2)
				return (0);
			if (access(path2, F_OK) == 0)
				c->path = ft_strdup(path2);
			free(path2);
		}
		if (!custom_path(c, env) && !c->path && !in_builtin(c->cmd_name))
			path_error(c, c->cmd_name, env);
		c = c->next;
	}
	return (1);
}

int	find_place_path(t_cmd_tab **cmd_struct, t_data *env)
{
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (ft_strnstr(env->var, "PATH", 4) != 0)
		{
			paths = ft_split((env->var + 5), ':');
			if (!paths)
				return (0);
			break ;
		}
		env = env->next;
	}
	if (!place_path(paths, *cmd_struct, env))
	{
		free_char_tab(paths);
		return (0);
	}
	free_char_tab(paths);
	return (1);
}
