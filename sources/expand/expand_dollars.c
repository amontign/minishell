/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:21:58 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 09:12:06 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Function that goes through the chained list to substitute
dollars in its command string.*/

/*Fonction qui parcours la liste chainee afin de substituer
les dollars presents dans une commande*/

int	expand_dollars(t_parsing **expand, t_data *env)
{
	t_parsing	*tmp;
	int			nb_dollars;

	tmp = *expand;
	while (tmp)
	{
		if (tmp->to_substitute)
		{
			nb_dollars = ft_intlen(&tmp->to_substitute);
			if (tmp->token_type != PIPE && nb_dollars > 0)
				tmp->cmd = substitute_dollars(&tmp, env, nb_dollars);
			if (ft_strcmp(tmp->cmd, "error") == 0)
				return (ft_printf("minishell: malloc error\n"), ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*The two functions below that replace the the dollars to substitute
and there name by its value, if it has one.*/

char	*substitute_dollars(t_parsing **tmp, t_data *env, int nb_dol)
{
	t_exp_dol	data;
	char		*new;
	int			diff_size;
	int			tab;

	if (f_dt_dol(&data, env, (*tmp), nb_dol) == ERROR)
		return (free((*tmp)->cmd), "error");
	diff_size = 0;
	tab = 0;
	while (data.size_value && tab < nb_dol)
	{
		diff_size += data.size_value[tab];
		tab++;
	}
	tab = -1;
	while (++tab < nb_dol)
		diff_size -= (*tmp)->dollar_size[tab];
	data.size_new = ft_strlen((*tmp)->cmd) + diff_size + 1;
	new = malloc(data.size_new * sizeof(char));
	new[0] = '\0';
	if (!new)
		return (free_data(&data), free((*tmp)->cmd), "error");
	tab = 0;
	subst_dols_2(&new, data, tmp, tab);
	return (free_data(&data), free((*tmp)->cmd), new);
}

void	subst_dols_2(char **new, t_exp_dol data, t_parsing **tmp, int tab)
{
	while (++data.i < ft_strlen((*tmp)->cmd))
	{
		data.k = -1;
		if (data.i == (*tmp)->to_substitute[tab])
		{
			if (data.size_value[tab] > 0)
				subst_dollars_3(&data, tab, new);
			data.i += (*tmp)->dollar_size[tab] - 1;
			tab++;
		}
		else
			new[0][++data.j] = (*tmp)->cmd[data.i];
	}
	if (data.j != -1)
	{
		if (new[0][data.j] != '\0')
			new[0][++data.j] = '\0';
	}
}

/*These two functions fill the data structure needed for the substitution
above, it gathers the name of the dollar, its value and the length of
its value*/

int	f_dt_dol(t_exp_dol *data, t_data *env, t_parsing *tmp, int nb_dol)
{
	int			tab;
	int			i;

	i = 0;
	tab = 0;
	if (malloc_data_strs(data, nb_dol) == ERROR)
		return (ft_printf("minishell: malloc error\n"), ERROR);
	(*data).env = env;
	while (tmp->cmd[i] && tab <= nb_dol)
	{
		if (i == tmp->to_substitute[tab])
		{
			if (fill_data_dol_2(data, tmp, &i, tab) == ERROR)
				return (free((*data).var_env), free((*data).value_var),
					free((*data).size_value), ERROR);
			tab++;
		}
		i++;
	}
	(*data).nb_tabs = tab;
	(*data).value_var[tab] = NULL;
	(*data).var_env[tab] = NULL;
	return (0);
}

int	fill_data_dol_2(t_exp_dol *data, t_parsing *tmp, int *j, int tab)
{
	int	i;

	i = 0;
	(*data).var_env[tab] = malloc((tmp->dollar_size[tab] + 1) * sizeof(char));
	if (!(*data).var_env[tab])
		return (ft_printf("minishell: malloc error\n"), ERROR);
	while (i < tmp->dollar_size[tab] - 1)
	{
		(*data).var_env[tab][i] = tmp->cmd[*j + 1];
		i++;
		*j += 1;
	}
	(*data).var_env[tab][i] = '\0';
	(*data).value_var[tab] = getenv_minish((*data).env, (*data).var_env[tab]);
	if ((*data).value_var[tab])
		fill_data_dol_3(data, tab);
	else
		(*data).size_value[tab] = 0;
	return (0);
}
