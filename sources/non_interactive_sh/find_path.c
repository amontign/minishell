/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:02:23 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/11 15:05:02 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_backslash(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*check_path(char *cmd, char *folder)
{
	int		i;
	int		j;
	char	*path;

	path = malloc((ft_strlen(folder) + ft_strcmd(cmd) + 2) * sizeof(char));
	if (!path)
		return (ft_printf("Malloc failed: path\n"), NULL);
	i = -1;
	j = -1;
	while (folder[++j])
		path[++i] = folder[j];
	path[++i] = '/';
	j = -1;
	while (cmd[++j])
		path[++i] = cmd[j];
	path[++i] = '\0';
	return (path);
}

char	*check_cmd(char *cmd, char **potential_paths)
{
	int		i;
	char	*path;

	i = -1;
	while (potential_paths[++i])
	{
		path = check_path(cmd, potential_paths[i]);
		if (!path)
			(ft_delete_str(potential_paths), free(potential_paths),
				exit (EXIT_FAILURE));
		else if (access(path, F_OK | X_OK) == 0)
			return (path);
		free (path);
	}
	return (NULL);
}

char	*find_path(char *cmd, char	**envp)
{
	int		i;
	char	*path;
	char	**potential_paths;

	i = 0;
	potential_paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			potential_paths = ft_split(envp[i] + 5, ':');
			if (!potential_paths)
				(ft_printf("Split failed: potential_paths\n"),
					exit (EXIT_FAILURE));
			break ;
		}
		i++;
	}
	if (!potential_paths)
		return (NULL);
	else
	{
		path = check_cmd(cmd, potential_paths);
		return (ft_delete_str(potential_paths), free (potential_paths), path);
	}
}
