/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:25:11 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:42:33 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab(t_data *env)
{
	int		i;
	char	**env_tab;
	t_data	*first;

	i = 0;
	first = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	i = 0;
	while (first)
	{
		env_tab[i] = ft_strdup(first->var);
		if (!env_tab[i])
			return (NULL);
		first = first->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	change_status(t_data *env, int status)
{
	char		*tmp;
	char		*tmp2;

	while (env)
	{
		if (ft_strncmp(env->var, "?=", 2) == 0)
		{
			free(env->var);
			tmp = ft_itoa(status);
			tmp2 = ft_strjoin("?=", tmp);
			free(tmp);
			env->var = ft_strdup(tmp2);
			free(tmp2);
			break ;
		}
		env = env->next;
	}
}

int	count_cmds(t_cmd_tab *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->exec)
			i++;
		cmd = cmd->next;
	}
	return (i);
}

void	init_exec(t_norm_exec *normy, t_cmd_tab **c_s)
{
	normy->num_cmds = 0;
	normy->input_fd = 0;
	normy->status = 0;
	normy->exit = 257;
	normy->output = 0;
	normy->pids = ft_calloc(sizeof(pid_t), count_cmds(*c_s));
}

int	in_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
	{
		return (1);
	}
	return (0);
}
