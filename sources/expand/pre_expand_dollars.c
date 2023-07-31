/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:18:06 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/30 18:08:49 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*The five functions below prepare the dollars expand. They remove the one
that can be already removed, skip those who are between single quotes
and fill two int arrays, to_substitute and dollar_size.*/

int	pre_expand_dollar(t_parsing **exp_dollar)
{
	t_parsing	*tmp;
	int			tab;
	int			i;

	tmp = *exp_dollar;
	while (tmp)
	{
		i = 0;
		tab = 0;
		if (tmp->token_type != TOKEN_PIPE)
			pre_expand_dollar_2(&tmp, &i, tab);
		tmp = tmp->next;
	}
	return (0);
}

int	pre_expand_dollar_2(t_parsing **tmp, int *i, int tab)
{
	while (*i < ft_strlen((*tmp)->cmd) && (*tmp)->cmd[*i])
	{
		if (pre_expand_dollar_3(tmp, i, 1, 0) == ERROR)
			return (ERROR);
		*i += 1;
	}
	if (how_many_dollars(tmp) == ERROR)
		return (ERROR);
	*i = 0;
	while (*i < ft_strlen((*tmp)->cmd) && (*tmp)->cmd[*i])
	{
		if (pre_expand_dollar_3(tmp, i, 2, &tab) == ERROR)
			return (ERROR);
		*i += 1;
	}
	return (0);
}

int	pre_expand_dollar_3(t_parsing **tmp, int *i, int choice, int *tab)
{
	int	set_back;

	set_back = 0;
	pre_expand_dollar_4(tmp, i, choice);
	if (pre_expand_dollar_5(tmp, i, choice, tab) == ERROR)
		return (ERROR);
	if (choice == 1 && (*tmp)->cmd[*i] == '$' && (*tmp)->cmd[*i + 1] != ' '
		&& (*tmp)->cmd[*i + 1] != '\0')
	{
		set_back = i_need_a_dollar(tmp, *i, choice, tab);
		if (set_back == ERROR)
			return (ERROR);
		*i -= set_back;
	}
	else if (choice == 2 && (*tmp)->cmd[*i] == '$' && ((*tmp)->cmd[*i + 1] == '?'
		|| ft_isalnum_env((*tmp)->cmd[*i + 1]) == TRUE) && am_a_lonesome_dollar((*tmp)->cmd, *i, 2) == FALSE)
	{
		set_back = i_need_a_dollar(tmp, *i, choice, tab);
		if (set_back == ERROR)
			return (ERROR);
		*i -= set_back;
	}
	return (0);
}

void	pre_expand_dollar_4(t_parsing **tmp, int *i, int choice)
{
	if ((*tmp)->cmd[*i] == SINGLE_QUOTE)
	{
		*i += 1;
		while ((*tmp)->cmd[*i] != SINGLE_QUOTE && (*tmp)->cmd[*i] != '\0')
			*i += 1;
	}
	if (choice == 1 && (*tmp)->cmd[*i] == DOUBLE_QUOTE)
	{
		*i += 1;
		while ((*tmp)->cmd[*i] != DOUBLE_QUOTE && (*tmp)->cmd[*i] != '\0')
			*i += 1;
	}
}

int	pre_expand_dollar_5(t_parsing **tmp, int *i, int choice, int *tab)
{
	int	set_back;

	set_back = 0;
	if (choice == 2 && (*tmp)->cmd[*i] == DOUBLE_QUOTE)
	{
		*i += 1;
		while ((*tmp)->cmd[*i] != DOUBLE_QUOTE && (*tmp)->cmd[*i] != '\0')
		{
			if ((*tmp)->cmd[*i] == '$'
				&& am_a_lonesome_dollar((*tmp)->cmd, *i, 1) == FALSE)
			{
				set_back = i_need_a_dollar(tmp, *i, choice, tab);
				if (set_back == ERROR)
					return (ERROR);
				*i -= set_back;
			}
			*i += 1;
		}
	}
	return (0);
}
