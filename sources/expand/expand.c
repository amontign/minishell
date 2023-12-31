/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:33:09 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 09:11:27 by cbernaze         ###   ########.fr       */
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
	if (arg[*i] == SINGLE_QUOTE && (*i == 0 || arg[*i - 1] != '\a'))
	{
		*quotes += 1;
		*i += 1;
		while ((arg[*i] != SINGLE_QUOTE || (arg[*i] == SINGLE_QUOTE
					&& *i > 0 && arg[*i - 1] == '\a')) && arg[*i] != '\0')
			*i += 1;
		*quotes += 1;
	}
	if (arg[*i] == DOUBLE_QUOTE && (*i == 0 || arg[*i - 1] != '\a'))
	{
		*quotes += 1;
		*i += 1;
		while ((arg[*i] != DOUBLE_QUOTE || (arg[*i] == DOUBLE_QUOTE
					&& *i > 0 && arg[*i - 1] == '\a')) && arg[*i] != '\0')
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
	new = malloc((size_str + 1) * sizeof(char));
	if (!new)
		return (ft_printf("minishell: malloc error\n"),
			free((*dt).tmp->cmd_split[(*dt).j]), NULL);
	i = -1;
	j = -1;
	tab = 0;
	while (++i < size_str && (*dt).tmp->cmd_split[(*dt).j][i])
	{
		while ((*dt).tmp->rmv_qt[dt->j][tab] >= 0
					&& i == (*dt).tmp->rmv_qt[(*dt).j][tab])
		{
			i++;
			tab++;
		}
		new[++j] = (*dt).tmp->cmd_split[(*dt).j][i];
	}
	return (new[++j] = '\0', free((*dt).tmp->cmd_split[(*dt).j]), new);
}

char	*remove_char(char *str)
{
	char		*new_str;
	int			i;
	int			j;

	i = -1;
	j = ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '\a')
			j--;
	}
	new_str = malloc((j + 1) * sizeof(char));
	if (new_str == NULL)
		(printf("Erreur d'allocation de mémoire\n"), exit(1));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '\a')
			new_str[j] = str[i];
		else
			j--;
		j++;
	}
	return (new_str[j] = '\0', free(str), new_str);
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
	special(expand);
}
