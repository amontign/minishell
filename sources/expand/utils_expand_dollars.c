/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_dollars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:54:46 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/11 11:36:18 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*This function mallocs all the variables that need it
in the structure type t_exp_dol.*/

int	malloc_data_strs(t_exp_dol *data, int nb_dol)
{
	(*data).var_env = malloc((nb_dol + 1) * sizeof(char *)); // malloc bieng
	if (!(*data).var_env)
		return (ERROR);
	(*data).value_var = malloc((nb_dol + 1) * sizeof(char *)); // malloc beau
	if (!(*data).value_var)
		return (free((*data).var_env), ERROR);
	(*data).size_value = malloc((nb_dol + 1) * sizeof(char *)); // malloc joli
	if (!(*data).size_value)
		return (free((*data).var_env), free((*data).value_var), ERROR);
	return (0);
}

/*This function frees the data structure used in the file expand_dollar.c.*/

void	free_data(t_exp_dol	*data)
{
	int	i;

	i = 0;
	free((*data).size_value);
	while (i < ft_strlen_plus((*data).value_var))
	{
		ft_printf("#%s\n", (*data).value_var[i]);
		free((*data).value_var[i]);
		i++;
	}
	i = 0;
	while (i < ft_strlen_plus((*data).var_env))
	{
		free((*data).var_env[i]);
		i++;
	}
	(free((*data).value_var), free((*data).var_env));
}

/*Functions used for the splitting of commands in split_args.c. It goes
through the string between quotes to count it as one argument only.*/

void	go_through_quotes(char *str, int *i)
{
	int	size_str;

	size_str = ft_strlen(str);
	if (*i < size_str && str[*i] == SINGLE_QUOTE)
	{
		*i += 1;
		while (str[*i] != SINGLE_QUOTE && str[*i])
			*i += 1;
	}
	if (*i < size_str && str[*i] == DOUBLE_QUOTE)
	{
		*i += 1;
		while (str[*i] != DOUBLE_QUOTE && str[*i])
			*i += 1;
	}
}

/*This function looks for the name of an environment variable,
if it exists its value is returned, otherwise NULL is returned.*/

char	*getenv_minish(t_data *data, char *var)
{
	t_data	*tmp;
	char	*value_var;
	int		size_var;

	tmp = data;
	var = ft_strjoin(var, "=");
	if (!var)
		return (NULL);
	value_var = NULL;
	size_var = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, size_var) == 0)
			return (free(var), value_var = ft_strdup(tmp->var + size_var));
		tmp = tmp->next;
	}
	return (free(var), NULL);
}
