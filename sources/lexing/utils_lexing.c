/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:36:57 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/30 18:44:51 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Attribue a un maillon l'index correspondant a sa position
dans une liste de type t_parsing*/

void	set_index(t_parsing **lexing)
{
	t_parsing	*tmp;
	int			i;

	i = 0;
	tmp = *lexing;
	while (tmp)
	{
		tmp->index = ++i;
		tmp = tmp->next;
	}
}

/* Dans le cas ou on a une redir, j'avance de un ou plus
selon la redir et son premiere argument dans ma string
et j'incremente mon comtpeur de token.*/

void	is_redir(char *cmd_line, char c, char c_plus_one, int *i)
{
	if ((c == '<' && c_plus_one != '<') || (c == '>' && c_plus_one != '>'))
		*i += 1;
	else if ((c == '<' && c_plus_one == '<')
		|| (c == '>' && c_plus_one == '>'))
		*i += 2;
	while (cmd_line[*i] == ' ')
		*i += 1;
	while (*i < ft_strlen(cmd_line)
		&& is_meta(cmd_line[*i], cmd_line[*i + 1]) == FALSE
		&& cmd_line[*i] != '\0' && cmd_line[*i] != ' ')
	{
		if (cmd_line[*i] == SINGLE_QUOTE)
		{
			*i += 1;
			while (cmd_line[*i] != SINGLE_QUOTE)
				*i += 1;
			*i += 1;
		}
		if (cmd_line[*i] == DOUBLE_QUOTE)
		{
			*i += 1;
			while (cmd_line[*i] != DOUBLE_QUOTE)
				*i += 1;
			*i += 1;
		}
		is_redir_2(cmd_line, i);
	}
}

void	is_redir_2(char *cmd_line, int *i)
{
	if (cmd_line[*i] == 34)
	{
		*i += 1;
		while (cmd_line[*i] != 34 && cmd_line[*i])
			*i += 1;
	}
	if (cmd_line[*i] == 39)
	{
		*i += 1;
		while (cmd_line[*i] != 39 && cmd_line[*i])
			*i += 1;
	}
	else
		*i += 1;
}

/*Determine si le symbole est un pipe ou une redir,
s'il est entre quotes on ne le prend pas en compte.*/

int	is_meta(char c, char c_plus_one)
{
	if (c == '|')
		return (PIPE);
	if ((c == '<' && c_plus_one != '<')
		|| (c == '>' && c_plus_one != '>')
		|| (c == '<' && c_plus_one == '<')
		|| (c == '>' && c_plus_one == '>'))
		return (REDIR);
	return (FALSE);
}

/*Determine a quel famille de token une commande appartient.*/

int	which_token_type(char	*cmd)
{
	if (!cmd)
		return (ERROR);
	if (cmd[0] == '|')
		return (TOKEN_PIPE);
	if (cmd[0] == '<' || cmd[0] == '>')
		return (TOKEN_REDIR);
	return (TOKEN_CMD);
}
