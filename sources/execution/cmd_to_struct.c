/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:01 by amontign          #+#    #+#             */
/*   Updated: 2023/07/15 15:42:06 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	place_path(char **paths, t_cmd_tab *cmd_struct)
{
	int		i;
	char	*path;
	char	*path2;

	while (cmd_struct)
	{
		i = 0;
		while (paths[i] && !cmd_struct->path)
		{
			path = ft_strjoin(paths[i], "/");
			path2 = ft_strjoin(path, cmd_struct->cmd_name);
			free(path);
			if (access(path2, F_OK) == 0)
			{
				cmd_struct->path = ft_strdup(path2);
			}
			free(path2);
			i++;
		}
		if (!cmd_struct->path)
			return (0);
		cmd_struct = cmd_struct->next;
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
			break ;
		}
		env = env->next;
	}
	if (!paths)
		return (0);
	if (!place_path(paths, *cmd_struct))
	{
		free_char_tab(paths);
		return (0);
	}
	free_char_tab(paths);
	return (1);
}

void	lexing_to_cmd_tab(t_parsing *lexing, t_cmd_tab **cmd_struct)
{
	int	id;

	id = 0;
	while (lexing)
	{
		if (lexing->token_type == TOKEN_CMD)
		{
			cmd_struct_add_back(cmd_struct,
				cmd_struct_new(lexing->cmd_split,
					ft_strdup(lexing->cmd_split[0]), id));
			id++;
		}
		lexing = lexing->next;
	}
}
