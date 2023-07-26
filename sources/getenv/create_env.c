/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:54:47 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/23 13:29:31 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*These two functions create 4 variables in case the environnement
is empty when minishell is launched.*/

int	create_env(t_data **data)
{
	t_data	*new;
	char	buf[FILENAME_MAX];
	char	*shlvl;
	char	*pwd;

	if (!getcwd(buf, FILENAME_MAX))
		return (ERROR);
	pwd = ft_strjoin("PWD=", buf);
	if (!pwd)
		return (ERROR);
	*data = ft_lstnew_data(pwd);
	if (!(*data))
		return (free(pwd), ERROR);
	shlvl = ft_strjoin("SHLVL=", "1");
	if (!shlvl)
		return (free(pwd), ft_lstclear_data(data), ERROR);
	new = ft_lstnew_data(shlvl);
	if (!new)
		return (free(pwd), ft_lstclear_data(data), free(shlvl), ERROR);
	ft_lstadd_back_data(data, new);
	if (create_env_2(data, buf) == ERROR)
		return (ERROR);
	return (0);
}

int	create_env_2(t_data **data, char *pwd)
{
	t_data	*new;
	char	*last_path;
	char	*exit_val;

	last_path = ft_strjoin(pwd, "/minishell");
	if (!last_path)
		return (ft_lstclear_data(data), ERROR);
	last_path = ft_strjoin("_=", last_path);
	if (!last_path)
		return (free(last_path), ft_lstclear_data(data), ERROR);
	new = ft_lstnew_data(last_path);
	if (!new)
		return (ft_lstclear_data(data), free(last_path), ERROR);
	ft_lstadd_back_data(data, new);
	exit_val = ft_strdup("?=0");
	if (!exit_val)
		return (free(last_path), ft_lstclear_data(data), ERROR);
	new = ft_lstnew_data(exit_val);
	if (!new)
		return (ft_lstclear_data(data), free(last_path), free(exit_val), ERROR);
	ft_lstadd_back_data(data, new);
	return (0);
}

/*Function that creates a chained list with the different environnement
variables, and creates the variables if the environnement is empty on launch.*/

int	ft_getenv(t_data **data, char **envp)
{
	int		i;
	t_data	*new;
	char	*exit_val;

	i = -1;
	if (!envp[0])
		create_env(data);
	else
	{
		while (envp[++i])
		{
			new = ft_lstnew_data(envp[i]);
			if (!new)
				return (ERROR);
			ft_lstadd_back_data(data, new);
		}
		exit_val = ft_strdup("?=0");
		if (!exit_val)
			return (ft_lstclear_data(data), ERROR);
		new = ft_lstnew_data(exit_val);
		if (!new)
			return (ft_lstclear_data(data), free(exit_val), ERROR);
		free(exit_val);
		ft_lstadd_back_data(data, new);
	}
	return (0);
}
