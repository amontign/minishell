/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:35:58 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 08:58:29 by amontign         ###   ########.fr       */
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
		while (env_tab[i][j] != '=' && env_tab[i][j])
			j++;
		tmp = malloc(sizeof(char) * (j + 2));
		if (!tmp)
			exit(1);
		(ft_strlcpy(tmp, env_tab[i], (j + 2)), ft_putstr_fd("declare -x ", fd));
		(ft_putstr_fd(tmp, fd), free(tmp));
		if (env_tab[i][j])
			(ft_putchar_fd('"', fd), ft_putstr_fd(env_tab[i] + j + 1, fd)
				, ft_putchar_fd('"', fd), ft_putchar_fd('\n', fd));
		i++;
	}
	free_char_tab(env_tab);
}

int	export_in_env(char *arg, t_data *env, int fd)
{
	int		i;
	t_data	*new;

	i = arg_is_valid(arg, fd);
	if (!i)
		return (1);
	while (env)
	{
		if (ft_strncmp(env->var, arg, i) == 0 && (env->var[i] == '\0'
				|| env->var[i] == '='))
		{
			if (arg[i] == '=')
				(free(env->var), env->var = ft_strdup(arg));
			return (0);
		}
		if (!env->next)
		{
			new = ft_lstnew_data(arg);
			env->next = new;
			new->previous = env;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	command_only(t_cmd_tab *current)
{
	if (current->next || current->prev)
	{
		return (0);
	}
	return (1);
}

int	export(char **args, t_data *env, int fd, t_cmd_tab *current)
{
	int	i;
	int	rslt;

	i = 1;
	rslt = 0;
	if (!args[1])
		export_no_args(env, fd);
	else if (command_only(current))
	{
		if (args[1][0] == '-' && args[1][1])
		{
			ft_putstr_fd("minishell: export: -", 2);
			ft_putchar_fd(args[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
			return (2);
		}
		while (args[i])
		{
			if (export_in_env(args[i], env, fd) == 1)
				rslt = 1;
			i++;
		}
	}
	return (rslt);
}
