/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:09:15 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 19:03:37 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*These three functions fill the array of int array rmv_qt in the
t_parsing chained list. I then goes to the function remo_cmd_quotes
so that the quotes that need to be remove are.*/

int	expand_cmd_quotes(t_parsing **expand)
{
	t_data_qt	dt;

	dt.tmp = *expand;
	while (dt.tmp)
	{
		if (dt.tmp->token_type == TOKEN_CMD)
		{
			dt.j = 0;
			if (how_many_cmd_quotes(&dt.tmp) == ERROR)
				return (ERROR);
			while (dt.tmp->cmd_split[dt.j])
			{
				expand_cmd_quotes_2(&dt.tmp, &dt, dt.tmp->cmd_split[dt.j]);
				dt.tmp->cmd_split[dt.j] = remove_cmd_quotes(&dt);
				dt.j++;
			}
		}
		dt.tmp = dt.tmp->next;
	}
	return (0);
}

void	expand_cmd_quotes_2(t_parsing **tmp, t_data_qt *dt, char *arg)
{
	int	size;

	(*dt).i = 0;
	(*dt).k = 0;
	size = ft_strlen(arg);
	while ((*dt).i < size && arg[(*dt).i])
	{
		if (arg[(*dt).i] == SINGLE_QUOTE && ((*dt).i == 0
				|| arg[(*dt).i - 1] != '\a'))
		{
			(*tmp)->rmv_qt[(*dt).j][(*dt).k] = (*dt).i;
			(*dt).i++;
			(*dt).k++;
			while ((arg[(*dt).i] != SINGLE_QUOTE
					|| ((*dt).i > 0 && arg[(*dt).i - 1] == '\a'))
				&& arg[(*dt).i] != '\0')
				(*dt).i++;
			(*tmp)->rmv_qt[(*dt).j][(*dt).k] = (*dt).i;
			(*dt).k++;
		}
		expand_cmd_quotes_3(tmp, dt, arg);
		(*dt).i++;
	}
}

void	expand_cmd_quotes_3(t_parsing **tmp, t_data_qt *dt, char *arg)
{
	if (arg[(*dt).i] == DOUBLE_QUOTE && ((*dt).i == 0
			|| arg[(*dt).i - 1] != '\a'))
	{
		(*tmp)->rmv_qt[(*dt).j][(*dt).k] = (*dt).i;
		(*dt).k += 1;
		(*dt).i += 1;
		while ((arg[(*dt).i] != DOUBLE_QUOTE
				|| ((*dt).i > 0 && arg[(*dt).i - 1] == '\a'))
			&& arg[(*dt).i] != '\0')
			(*dt).i += 1;
		(*tmp)->rmv_qt[(*dt).j][(*dt).k] = (*dt).i;
		(*dt).k += 1;
	}
}

/*These two functions are used to determine
which quotes are to be removed in command tokens.
A third function is needed for that, it is in the expand.c file.*/

int	how_many_cmd_quotes(t_parsing **tmp)
{
	int	size_tab;
	int	nb_quotes;
	int	tab;

	tab = 0;
	nb_quotes = 0;
	size_tab = ft_strlen_plus((*tmp)->cmd_split);
	(*tmp)->rmv_qt = malloc((size_tab + 1) * sizeof(int *)); //malloc superr
	if (!(*tmp)->rmv_qt)
		return (ft_printf("minishell: malloc error\n"), ERROR);
	while (tab < size_tab && (*tmp)->cmd_split[tab])
	{
		nb_quotes = how_many_cmd_quotes_2(tmp, tab);
		if (nb_quotes == ERROR)
			return (ERROR);
		tab++;
	}
	(*tmp)->rmv_qt[size_tab] = NULL;
	return (0);
}

int	how_many_cmd_quotes_2(t_parsing **tmp, int tab)
{
	int	size_str;
	int	quotes;
	int	i;

	i = 0;
	quotes = 0;
	size_str = ft_strlen((*tmp)->cmd_split[tab]);
	while (i < size_str && (*tmp)->cmd_split[tab][i])
		how_many_cmd_quotes_3((*tmp)->cmd_split[tab], &i, &quotes);
	(*tmp)->rmv_qt[tab] = malloc((quotes + 1) * sizeof(int)); //malloc ok
	if (!(*tmp)->rmv_qt[tab])
		return (ft_printf("minishell: malloc error\n"), ERROR);
	i = 0;
	while (i <= quotes)
	{
		(*tmp)->rmv_qt[tab][i] = -1;
		i++;
	}
	return (0);
}
