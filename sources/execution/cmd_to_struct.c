/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:01 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:19:34 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(t_cmd_tab *cmd_struct, t_data *env)
{
	struct stat	s;

	if (stat(cmd_struct->path, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_struct->path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			cmd_struct->exec = 0;
			change_status(env, 126);
			return (1);
		}
	}
	return (0);
}

int	c_r_s(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || (str[i] > 8 && str[i] < 14)
		|| str[i] == ' ')
	{
		i++;
	}
	return (i);
}

int	command_find(t_parsing *iter)
{
	int			cmd_find;
	t_parsing	*tmp;

	cmd_find = 0;
	tmp = iter;
	while (tmp->previous)
	{
		tmp = tmp->previous;
		if (tmp->token_type == TOKEN_CMD)
			cmd_find = 1;
		else if (tmp->token_type == TOKEN_PIPE)
			break ;
	}
	tmp = iter;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->token_type == TOKEN_CMD)
			cmd_find = 1;
		else if (tmp->token_type == TOKEN_PIPE)
			break ;
	}
	return (cmd_find);
}

void	add_true_cmd(t_parsing **lexing)
{
	t_parsing	*iter;
	t_parsing	*new_cmd;

	iter = *lexing;
	while (iter)
	{
		if (iter->token_type == TOKEN_REDIR)
		{
			if (!command_find(iter))
			{
				new_cmd = ft_lstnew_minishell("true", 4, TOKEN_CMD);
				new_cmd->next = iter->next;
				new_cmd->previous = iter;
				new_cmd->cmd_split = ft_split(new_cmd->cmd, ' ');
				if (iter->next)
					iter->next->previous = new_cmd;
				iter->next = new_cmd;
			}
		}
		iter = iter->next;
	}
}

void	lexing_to_cmd_tab(t_parsing *lexing, t_cmd_tab **c, t_data *env)
{
	int			id;
	t_parsing	*lexing_start;

	id = 0;
	add_true_cmd(&lexing);
	lexing_start = lexing;
	while (lexing)
	{
		if (lexing->token_type == TOKEN_CMD)
		{
			cmd_struct_add_back(c,
				cmd_struct_new(lexing->cmd_split,
					ft_strdup(lexing->cmd_split[0]), id));
			id++;
		}
		lexing = lexing->next;
	}
	put_redirects(lexing_start, c, env);
}
