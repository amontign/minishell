/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_custom_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:19:01 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:20:36 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	custom_path_e1(t_cmd_tab *cmd_struct, t_data *env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_struct->path, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	cmd_struct->exec = 0;
	change_status(env, 126);
	return (0);
}

int	custom_path_e2(t_cmd_tab *cmd_struct, t_data *env)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_struct->path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	change_status(env, 127);
	cmd_struct->exec = 0;
	return (0);
}

int	custom_path(t_cmd_tab *cmd_struct, t_data *env)
{
	int		i;
	char	*tmp;

	if (!cmd_struct->cmd_name)
		return (0);
	i = ft_strlen(cmd_struct->cmd_name) - 1;
	while (i >= 0 && cmd_struct->cmd_name[i] && cmd_struct->cmd_name[i] != '/')
		i--;
	if (i == -1)
		return (0);
	tmp = ft_strdup(cmd_struct->cmd_name);
	if (cmd_struct->path)
		free(cmd_struct->path);
	cmd_struct->path = ft_strdup(tmp);
	free(tmp);
	if (is_directory(cmd_struct, env))
		return (1);
	else if (access(cmd_struct->path, X_OK) == 0)
		return (1);
	else
	{
		if (access(cmd_struct->path, F_OK) == 0)
			return (custom_path_e1(cmd_struct, env));
		return (custom_path_e2(cmd_struct, env));
	}
}
