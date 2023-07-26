/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:26:31 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/25 16:15:50 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Structure de la honte que j'ai du creer pour faire rentrer
les 2 fonctions precedentes dans la norme*/

t_concatcmd	init_concatcmd(t_parsing *tmp)
{
	t_concatcmd	concat;

	concat.to_concat = tmp;
	concat.cmd1 = NULL;
	concat.cmd2 = concat.to_concat->cmd;
	return (concat);
}

void	free_cmds(char **cmd1, char **cmd2)
{
	if (*cmd1)
		free(*cmd1);
	if (*cmd2)
		free(*cmd2);
}

int	check_empty_cmd(t_parsing **lexing)
{
	t_parsing	*tmp;
	char		*error_pipe;
	int			i;

	error_pipe = ft_strdup("syntax error near unexpected token `|'");
	tmp = *lexing;
	while (tmp)
	{
		i = 0;
		while ((tmp->cmd[i] == ' ' || (tmp->cmd[i] > 6 && tmp->cmd[i] < 14)) && tmp->cmd[i])
			i++;
		if (tmp->previous && tmp->cmd[i] == '\0'
			&& tmp->previous->token_type == TOKEN_PIPE)
			return (ft_printf("minishell: %s\n", error_pipe),
				ft_lstclear_minishell(lexing), TRUE);
		if (tmp->cmd[i] == '\0')
			return (ft_lstclear_minishell(lexing), TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

/*The big bang of minishell*/

t_parsing	*tokenisation(char	*cmd_line)
{
	t_parsing	*lexing;

	lexing = NULL;
	if (split_cmd(&lexing, cmd_line) == ERROR)
		return (NULL);
	if (check_empty_cmd(&lexing) == TRUE)
		return (NULL);
	return (lexing);
}
