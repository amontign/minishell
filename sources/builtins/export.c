/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:35:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/25 13:13:22 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tri_tab(char **arr)
{
	char	*temp;
	int		n;
	int		i;
	int		j;

	n = 0;
	while (arr[n] != NULL)
		++n;
	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	export_no_args(t_data *env, int fd)
{
	int		i;
	int		j;
	char	**env_tab;
	char	*tmp;

	(void)fd;
	env_tab = env_to_tab(env);
	tri_tab(env_tab);
	i = 0;
	while (env_tab[i])
	{
		j = 0;
		while (env_tab[i][j] != '=')
			j++;
		tmp = malloc(sizeof(char) * (j + 2));
		ft_strlcpy(tmp, env_tab[i], (j + 2));
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp, fd);
		free(tmp);
		ft_putchar_fd('"', fd);
		ft_putstr_fd(env_tab[i] + j + 1, fd);
		ft_putstr_fd("\"\n", fd);
		i++;
	}
	free_char_tab(env_tab);
}

void	builtin_export(char **args, t_data *env, int fd)
{
	if (!args[1])
	{
		export_no_args(env, fd);
		return ;
	}
}
