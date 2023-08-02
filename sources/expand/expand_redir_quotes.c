/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:44:18 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 19:06:51 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*These two functions go through the chained list and fill the
int array rmv_qt which keeps the positions of the quotes
to remove later.*/

int	expand_redir_quotes(t_parsing **expand)
{
	t_data_qt	dt;

	dt.tmp = *expand;
	dt.nb_quotes = 0;
	while (dt.tmp)
	{
		if (dt.tmp->token_type == TOKEN_REDIR)
		{
			dt.i = 0;
			dt.j = 0;
			dt.nb_quotes = how_many_redir_quotes(&dt.tmp);
			if (dt.nb_quotes == 0)
			{
				while (dt.i < ft_strlen(dt.tmp->cmd) && dt.tmp->cmd[dt.i])
					expand_redir_quotes_2(&dt.tmp, &dt.i, &dt.j);
				dt.tmp->cmd = rmv_redir_quotes(dt.tmp->cmd, dt.tmp->rmv_qt[0]);
				if (dt.tmp->cmd == NULL)
					return (ERROR);
			}
			else if (dt.nb_quotes == ERROR)
				return (ERROR);
		}
		dt.tmp = dt.tmp->next;
	}
	return (0);
}

void	expand_redir_quotes_2(t_parsing **tmp, int *i, int *j)
{
	if ((*tmp)->cmd[*i] == SINGLE_QUOTE
		&& (*i == 0 || (*tmp)->cmd[*i - 1] != '\a'))
	{
		(*tmp)->rmv_qt[0][*j] = *i;
		*j += 1;
		*i += 1;
		while (((*tmp)->cmd[*i] != SINGLE_QUOTE || (*i > 0
					&& (*tmp)->cmd[*i - 1] == '\a')) && (*tmp)->cmd[*i] != '\0')
			*i += 1;
		(*tmp)->rmv_qt[0][*j] = *i;
		*j += 1;
	}
	if ((*tmp)->cmd[*i] == DOUBLE_QUOTE
		&& (*i == 0 || (*tmp)->cmd[*i - 1] != '\a'))
	{
		(*tmp)->rmv_qt[0][*j] = *i;
		*j += 1;
		*i += 1;
		while (((*tmp)->cmd[*i] != DOUBLE_QUOTE || (*i > 0
					&& (*tmp)->cmd[*i - 1] == '\a')) && (*tmp)->cmd[*i] != '\0')
			*i += 1;
		(*tmp)->rmv_qt[0][*j] = *i;
		*j += 1;
	}
	*i += 1;
}

/*These two functions count the number of quotes that will be removed.*/

int	how_many_redir_quotes(t_parsing **tmp)
{
	int	size_tab;
	int	i;

	size_tab = 0;
	i = 0;
	while (i < ft_strlen((*tmp)->cmd) && (*tmp)->cmd[i])
		how_many_redir_quotes_2(tmp, &i, &size_tab);
	if (size_tab == 0)
		return (-2);
	(*tmp)->rmv_qt = malloc(sizeof(int *) * 2); //malloc fabuleux
	if (!((*tmp)->rmv_qt))
		return (ft_printf("minishell: malloc error\n"), ERROR);
	(*tmp)->rmv_qt[0] = malloc((size_tab + 1) * sizeof(int)); //malloc incroyable
	if (!((*tmp)->rmv_qt[0]))
		return (ft_printf("minishell: malloc error\n"), ERROR);
	(*tmp)->rmv_qt[1] = NULL;
	i = 0;
	while (i <= size_tab)
	{
		(*tmp)->rmv_qt[0][i] = -1;
		i++;
	}
	return (0);
}

void	how_many_redir_quotes_2(t_parsing **tmp, int *i, int *size_tab)
{
	if ((*tmp)->cmd[*i] == SINGLE_QUOTE)
	{
		*size_tab += 1;
		*i += 1;
		while ((*tmp)->cmd[*i] != SINGLE_QUOTE && (*tmp)->cmd[*i] != '\0')
			*i += 1;
		*size_tab += 1;
	}
	if ((*tmp)->cmd[*i] == DOUBLE_QUOTE)
	{
		*size_tab += 1;
		*i += 1;
		while ((*tmp)->cmd[*i] != DOUBLE_QUOTE && (*tmp)->cmd[*i] != '\0')
			*i += 1;
		*size_tab += 1;
	}
	*i += 1;
}

/*This function remove the quotes that can be removed.*/

char	*rmv_redir_quotes(char *str, int *quote_pos)
{
	char	*new;
	int		size_str;
	int		tab;
	int		i;
	int		j;

	size_str = ft_strlen(str);
	new = malloc((size_str + 1) * sizeof(char)); //malloc bg
	if (!new)
		return (ft_printf("minishell: malloc error\n"), free(str), NULL);
	i = 0;
	j = 0;
	tab = 0;
	while (i < size_str && str[i])
	{
		while (quote_pos[tab] >= 0 && i == quote_pos[tab])
		{
			i++;
			tab++;
		}
		new[j] = str[i];
		i++;
		j++;
	}
	return (new[j] = '\0', free(str), new);
}
