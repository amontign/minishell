/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:07:22 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/01 07:58:43 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Funtion that count the number of arguments in a command, command included.*/

void	arg_count(t_parsing *tmp, int *nb_arg)
{
	int	size_str;
	int	i;

	size_str = ft_strlen(tmp->cmd);
	i = 0;
	while (i < size_str)
	{
		while (i < size_str && (tmp->cmd[i] == ' ' || tmp->cmd[i] == '\t'))
			i++;
		if (i < size_str && tmp->cmd[i] != ' ' && tmp->cmd[i] != '\t')
			*nb_arg += 1;
		while (i < size_str && tmp->cmd[i] != ' ' && tmp->cmd[i] != '\t')
		{
			go_through_quotes(tmp->cmd, &i);
			i++;
		}
	}
}

/*Function that calculate the length of an argument.*/

int	len_arg(char *str)
{
	int	len;
	int	size_str;

	len = 0;
	size_str = ft_strlen(str);
	while (len < size_str && str[len] != ' ' && str[len] != '\t')
	{
		if (str[len] == SINGLE_QUOTE && (len == 0 || str[len - 1] != '\a'))
		{
			len += 1;
			while (str[len] != SINGLE_QUOTE && str[len])
				len += 1;
		}
		if (str[len] == DOUBLE_QUOTE && (len == 0 || str[len - 1] != '\a'))
		{
			len += 1;
			while (str[len] != DOUBLE_QUOTE && str[len])
				len += 1;
		}
		len++;
	}
	return (len);
}

/*Function that fills a sub_tab with an argument.*/

int	create_arg(char *str, char ***split, int *i, int *j)
{
	int	len;
	int	k;

	k = 0;
	len = len_arg(str + *i);
	if (len == 0)
		return (0);
	split[0][*j] = malloc((len + 1) * sizeof(char)); //malloc ouiii
	if (!split[0][*j])
		return (ft_printf("minishell: malloc error\n"), ERROR);
	while (k < len && str[*i])
	{
		split[0][*j][k] = str[*i];
		k++;
		*i += 1;
	}
	split[0][*j][k] = '\0';
	*j += 1;
	return (0);
}

/*Function that goes through the command to split it into
different arguments.*/

int	trim_args(t_parsing **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*tmp)->cmd[i])
	{
		while (((*tmp)->cmd[i] == ' ' || (*tmp)->cmd[i] == '\t')
			&& (*tmp)->cmd[i])
			i++;
		if (create_arg((*tmp)->cmd, &(*tmp)->cmd_split, &i, &j) == ERROR)
			return (ERROR);
	}
	return (0);
}

/*Function that organizes the split of the different commands
contained a command line.*/

int	split_args(t_parsing **expand)
{
	t_parsing	*tmp;
	int			nb_arg;

	tmp = *expand;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_CMD)
		{
			nb_arg = 0;
			arg_count(tmp, &nb_arg);
			tmp->cmd_split = malloc((nb_arg + 1) * sizeof(char *)); //malloc choueeette
			if (!tmp->cmd_split)
				return (ft_printf("minishell: malloc error\n"), ERROR);
			tmp->cmd_split[nb_arg] = NULL;
			if (trim_args(&tmp) == ERROR)
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}
