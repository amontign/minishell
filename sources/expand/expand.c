/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:33:09 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/31 15:03:55 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*This function is used in */

int	ft_isalnum_env(int c)
{
	if ((c > 47 && c < 58)
		|| (c > 64 && c < 91)
		|| (c > 96 && c < 123)
		|| c == 95
		|| c == 10)
		return (TRUE);
	else
		return (FALSE);
}

/*This is the third function used in expand_cmd_quotes.c to determine
which quotes are to be removed in command tokens.*/

void	how_many_cmd_quotes_3(char *arg, int *i, int *quotes)
{
	if (arg[*i] == SINGLE_QUOTE)
	{
		*quotes += 1;
		*i += 1;
		while (arg[*i] != SINGLE_QUOTE && arg[*i] != '\0')
			*i += 1;
		*quotes += 1;
	}
	if (arg[*i] == DOUBLE_QUOTE)
	{
		*quotes += 1;
		*i += 1;
		while (arg[*i] != DOUBLE_QUOTE && arg[*i] != '\0')
			*i += 1;
		*quotes += 1;
	}
	*i += 1;
}

/*This function is used in expand_cmd_quotes.c to
remove the quotes that can be removed.*/

char	*remove_cmd_quotes(t_data_qt *dt)
{
	char	*new;
	int		size_str;
	int		tab;
	int		i;
	int		j;

	size_str = ft_strlen((*dt).tmp->cmd_split[(*dt).j]);
	new = malloc((size_str + 1) * sizeof(char)); //malloc fantastique
	if (!new)
		return (ft_printf("minishell: malloc error\n"),
			free((*dt).tmp->cmd_split[(*dt).j]), NULL);
	i = -1;
	j = 0;
	tab = 0;
	while (++i < size_str && (*dt).tmp->cmd_split[(*dt).j][i])
	{
		while ((*dt).tmp->rmv_qt[dt->j][tab] >= 0 && i == (*dt).tmp->rmv_qt[(*dt).j][tab])
		{
			i++;
			tab++;
		}
		new[j] = (*dt).tmp->cmd_split[(*dt).j][i];
		j++;
	}
	return (new[j] = '\0', free((*dt).tmp->cmd_split[(*dt).j]), new);
}

/*This function organizes the different expands done before
the execution of the cmd line.*/

void	expand(t_parsing **expand, t_data *env)
{
	if (pre_expand_dollar(expand) == ERROR)
		return (ft_lstclear_minishell(expand));
	if (expand_dollars(expand, env) == ERROR)
		return (ft_lstclear_minishell(expand));
	if (split_args(expand) == ERROR)
		return (ft_lstclear_minishell(expand));
	if (expand_cmd_quotes(expand) == ERROR)
		return (ft_lstclear_minishell(expand));
	if (expand_redir_quotes(expand) == ERROR)
		return (ft_lstclear_minishell(expand));
}
