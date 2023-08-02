/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:35:56 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/02 12:45:27 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Calcule la longueur d'un token*/

int	len_cmd(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[len] == '|')
		return (1);
	if (cmd[len] == '<' || cmd[len] == '>')
		return (is_redir(cmd, cmd[len], cmd[len + 1], &len), len);
	while (len < ft_strlen(cmd) && is_meta(cmd[len], cmd[len + 1]) == FALSE)
	{
		if (cmd[len] == SINGLE_QUOTE)
		{
			len++;
			while (cmd[len] != SINGLE_QUOTE && cmd[len] != '\0')
				len++;
		}
		if (cmd[len] == DOUBLE_QUOTE)
		{
			len++;
			while (cmd[len] != DOUBLE_QUOTE && cmd[len] != '\0')
				len++;
		}
		len++;
	}
	return (len);
}

/*Rempli les differents maillons avec les differentes commandes separees*/

char	*trim_cmd(char	*cmd_line, int *i, int *len)
{
	char	*sub_tab;
	int		j;

	j = 0;
	*len = len_cmd(cmd_line);
	if (*len > ARG_MAX_MINISH)
		return (ft_printf("minishell: command size too long\n"), NULL);
	sub_tab = malloc(((*len) + 1) * sizeof(char));
	if (!sub_tab)
		return (ft_printf("minishell: malloc error\n"), NULL);
	while (j < *len)
	{
		sub_tab[j] = cmd_line[j];
		*i += 1;
		j++;
	}
	sub_tab[j] = '\0';
	return (sub_tab);
}

/*Fonction qui concatene les cmds de deux maillons differents
d'une liste de type t_parsing*/

void	concatenate_cmds(t_parsing **lexing, t_parsing *node)
{
	t_parsing	*tmp;
	t_concatcmd	concat;
	t_parsing	*original;

	original = *lexing;
	tmp = *lexing;
	while (tmp->index != node->index)
		tmp = tmp->next;
	concat = init_concatcmd(tmp->next);
	tmp->next = concat.to_concat->next;
	if (tmp->next)
		tmp->next->previous = tmp;
	while (tmp && tmp->token_type == TOKEN_REDIR)
		tmp = tmp->previous;
	if (tmp && tmp->token_type == TOKEN_CMD)
	{
		concat.cmd1 = tmp->cmd;
		tmp->cmd = ft_strjoin(tmp->cmd, concat.to_concat->cmd);
		tmp->size += concat.to_concat->size;
		(free_cmds(&concat.cmd1, &concat.cmd2), clear_node(&concat.to_concat));
	}
	else if (tmp && tmp->token_type != TOKEN_CMD)
	{
		tmp = *lexing;
		ft_lstadd_back_minishell(&tmp, concat.to_concat);
	}
	else
		lexing = &original;
	(set_index(lexing));
}

/*Parce que sinon ca serait trop simple, une petite fonction qui va concatener
des commandes si elles sont coupees par des redirections.*/

void	commands_assemble(t_parsing **lexing)
{
	t_parsing	*tmp;

	tmp = *lexing;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_REDIR && tmp->next)
		{
			if (tmp->next->token_type == TOKEN_CMD && tmp->previous)
				concatenate_cmds(lexing, tmp);
		}
		tmp = tmp->next;
	}
	tmp = *lexing;
}

/*Fonction qui split les tokens et les range dans un liste chainee*/

int	split_cmd(t_parsing **lexing, char *cmd_line)
{
	t_parsing	*new_node;
	char		*token;
	int			size_cmd;
	int			token_type;
	int			i;

	i = 0;
	while (cmd_line[i])
	{
		size_cmd = 0;
		token_type = 0;
		while ((cmd_line[i] == ' ' || cmd_line[i] == '\t') && cmd_line[i])
			i++;
		token = trim_cmd(cmd_line + i, &i, &size_cmd);
		if (!token)
			return (ft_lstclear_minishell(lexing), ERROR);
		token_type = which_token_type(token);
		new_node = ft_lstnew_minishell(token, size_cmd, token_type);
		if (!new_node)
			break ;
		ft_lstadd_back_minishell(lexing, new_node);
		free (token);
	}
	(set_index(lexing), commands_assemble(lexing));
	return (0);
}
