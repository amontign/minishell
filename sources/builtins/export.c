/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:35:58 by amontign          #+#    #+#             */
/*   Updated: 2023/07/27 10:58:35 by amontign         ###   ########.fr       */
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

int	arg_is_valid(char *arg, int fd)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
	{
		ft_putstr_fd("minishell: export: `", fd);
		ft_putstr_fd(arg, fd);
		ft_putstr_fd("': not a valid identifier\n", fd);
		return (0);
	}
	while (arg[i] != '=' && arg[i])
	{
		if (!(arg[i] > 47 && arg[i] < 58) && !(arg[i] > 64 && arg[i] < 91) && !(arg[i] > 96 && arg[i] < 123) && arg[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", fd);
			ft_putstr_fd(arg, fd);
			ft_putstr_fd("': not a valid identifier\n", fd);
			return (0);
		}
		i++;
	}
	if (arg[i] != '=')
		return (0);
	return (i);
}

void	export_in_env(char *arg, t_data *env, int fd)
{
	int		i;
	t_data	*new;

	i = arg_is_valid(arg, fd);
	if (!i)
		return ;
	while (env)
	{
		if (ft_strncmp(env->var, arg, i + 1) == 0)
		{
			free(env->var);
			env->var = ft_strdup(arg);
			return ;
		}
		if (!env->next)
		{
			new = ft_lstnew_data(arg);
			env->next = new;
			return ;
		}
		env = env->next;
	}
}

int	builtin_export(char **args, t_data *env, int fd)
{
	int	i;

	i = 1;
	if (!args[1])
		export_no_args(env, fd);
	else
	{
		if (args[1][0] == '-' && args[1][1])
		{
			ft_putstr_fd("minishell: export: -", 2);
			ft_putchar_fd(args[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
			return ;
		}
		while (args[i])
		{
			export_in_env(args[i], env, fd);
			i++;
		}
	}
	return (0);
}
