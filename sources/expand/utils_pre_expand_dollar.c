/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pre_expand_dollar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:55:24 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 19:13:23 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*This function tells if a dollar is alone, meaning it doesn' have a letter
or number or _ next to it.*/

int	am_a_lonesome_dollar(char *cmd, int dollar_pos, int choice)
{
	if (choice == 1 && ft_isalnum_env(cmd[dollar_pos + 1]) == FALSE)
		return (TRUE);
	if (dollar_pos >= 2)
	{
		if (cmd[dollar_pos - 1] == '<' && cmd[dollar_pos - 2] == '<')
			return (TRUE);
	}
	if (dollar_pos >= 3)
	{
		if (((cmd[dollar_pos - 1] == SINGLE_QUOTE
					|| cmd[dollar_pos - 1] == DOUBLE_QUOTE)
				&& cmd[dollar_pos - 2] == '<'
				&& cmd[dollar_pos - 3] == '<'))
			return (TRUE);
	}
	return (FALSE);
}

/*These two functions count the number of dollars needed to be substituted.*/

int	how_many_dollars(t_parsing **tmp)
{
	int	size_subt_tab;
	int	i;

	size_subt_tab = 0;
	i = 0;
	while (i < ft_strlen((*tmp)->cmd) && (*tmp)->cmd[i])
		how_many_dollars_2(tmp, &i, &size_subt_tab);
	if (size_subt_tab == 0)
		return (-2);
	(*tmp)->to_substitute = malloc((size_subt_tab + 1) * sizeof(int)); //malloc jtm
	if (!((*tmp)->to_substitute))
		return (ft_printf("minishell: malloc error\n"), ERROR);
	(*tmp)->dollar_size = malloc((size_subt_tab + 1) * sizeof(int)); //malloc sublime
	if (!((*tmp)->dollar_size))
		return (ft_printf("minishell: malloc error\n"), ERROR);
	i = 0;
	while (i <= size_subt_tab)
	{
		(*tmp)->to_substitute[i] = -1;
		i++;
	}
	return (0);
}

void	how_many_dollars_2(t_parsing **tmp, int *i, int *size_subt_tab)
{
	if ((*tmp)->cmd[*i] == SINGLE_QUOTE)
	{
		*i += 1;
		while ((*tmp)->cmd[*i] != SINGLE_QUOTE && (*tmp)->cmd[*i] != '\0')
			*i += 1;
	}
	if ((*tmp)->cmd[*i] == DOUBLE_QUOTE)
	{
		*i += 1;
		while ((*tmp)->cmd[*i] != DOUBLE_QUOTE && (*tmp)->cmd[*i] != '\0')
		{
			if ((*tmp)->cmd[*i] == '$'
				&& am_a_lonesome_dollar((*tmp)->cmd, *i, 1) == FALSE)
				*size_subt_tab += 1;
			*i += 1;
		}
	}
	if ((*tmp)->cmd[*i] == '$')
		*size_subt_tab += 1;
	*i += 1;
}

/*This function removes that can be removed before the expand. There are two
cases echo $'test' and echo $"test".*/

char	*remove_dollar(char *str, int dol_pos)
{
	char	*new;
	int		size_str;
	int		i;
	int		j;

	size_str = ft_strlen(str);
	new = malloc((size_str) * sizeof(char)); // malloc cool
	if (!new)
		return (ft_printf("minishell: malloc error\n"), free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i == dol_pos)
			i++;
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (free(str), new);
}

/*This function either goes to remove dollar (see above) or
keeps the size of an environmment variable.*/

int	i_need_a_dollar(t_parsing **tmp, int dol_pos, int choice, int *tab)
{
	int	i;

	if (choice == 1 && ((*tmp)->cmd[dol_pos + 1] == DOUBLE_QUOTE
			|| (*tmp)->cmd[dol_pos + 1] == SINGLE_QUOTE))
	{
		(*tmp)->cmd = remove_dollar((*tmp)->cmd, dol_pos);
		if ((*tmp)->cmd == NULL)
			return (ERROR);
		return (1);
	}
	else if (choice == 2)
	{
		i = 0;
		(*tmp)->to_substitute[*tab] = dol_pos;
		(*tmp)->dollar_size[*tab] = 1;
		if ((*tmp)->cmd[dol_pos + 1] == '?'
			|| ft_isdigit((*tmp)->cmd[dol_pos + 1]))
			(*tmp)->dollar_size[*tab] += 1;
		while (ft_isalnum_dol((*tmp)->cmd[++dol_pos], ++i) == TRUE)
			(*tmp)->dollar_size[*tab] += 1;
		*tab += 1;
	}
	return (0);
}
