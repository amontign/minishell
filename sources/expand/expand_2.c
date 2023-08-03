/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:11:08 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 09:12:31 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	special(t_parsing **expand)
{
	int			i;
	t_parsing	*actual;

	actual = *expand;
	while (actual)
	{
		i = 0;
		while (actual->cmd_split && actual->cmd_split[i])
		{
			actual->cmd_split[i] = remove_char(actual->cmd_split[i]);
			i++;
		}
		actual = actual->next;
	}
}

void	subst_dollars_3(t_exp_dol *data, int tab, char **new)
{
	while (data->value_var[tab][++data->k])
	{
		if (data->value_var[tab][data->k] == '"'
			|| data->value_var[tab][data->k] == '\'')
		{
			new[0][++data->j] = '\a';
			new[0][++data->j] = data->value_var[tab][data->k];
		}
		else
			new[0][++data->j] = data->value_var[tab][data->k];
	}
}

void	fill_data_dol_3(t_exp_dol *data, int tab)
{
	int	i;

	(*data).size_value[tab] = ft_strlen((*data).value_var[tab]);
	i = -1;
	while ((*data).value_var[tab][++i])
	{
		if ((*data).value_var[tab][i] == '"'
			|| (*data).value_var[tab][i] == '\'')
			(*data).size_value[tab] += 1;
	}
}

void	len_arg_2(char *str, int *len)
{
	*len += 1;
	while (str[*len])
	{
		if (str[*len] != DOUBLE_QUOTE)
			*len += 1;
		else if (str[*len] == DOUBLE_QUOTE
			&& *len > 0 && str[*len - 1] != '\a' && str[*len])
			break ;
		else
			*len += 1;
	}
}
