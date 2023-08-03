/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:09:34 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:16:56 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_files(t_cmd_tab	*first, char *str)
{
	if (str[1] == '>')
	{
		first->outfile_delete = 0;
		close(open(first->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644));
	}
	else
		close(open(first->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	put_redirect(t_cmd_tab *cmd_struct, char *str, int id, t_data *env)
{
	t_cmd_tab	*first;

	first = cmd_struct;
	if (!str || !str[0] || !str[1])
		return (2);
	while (first)
	{
		if (first->id == id)
			break ;
		first = first->next;
	}
	if (str[0] == '>')
	{
		first->outfile = str + c_r_s(str);
		create_files(first, str);
	}
	else
	{
		if (str[1] == '<')
			first->heredoc = heredoc_complete(str + c_r_s(str), env);
		else
			first->infile = str + c_r_s(str);
	}
	return (1);
}

void	put_redirects(t_parsing *lexing, t_cmd_tab **c, t_data *env)
{
	t_parsing	*lexing2;
	int			id;
	int			put_r;

	id = 0;
	while (lexing)
	{
		if (lexing->token_type == TOKEN_CMD)
			id++;
		else if (lexing->token_type == TOKEN_REDIR)
		{
			put_r = 0;
			lexing2 = lexing;
			while (lexing2 && lexing2->token_type != TOKEN_PIPE)
			{
				if (lexing2->token_type == TOKEN_CMD)
					put_r = put_redirect(*c, lexing->cmd,
							(id - 1), env);
				lexing2 = lexing2->previous;
			}
			if (put_r == 0)
				put_redirect(*c, lexing->cmd, id, env);
		}
		lexing = lexing->next;
	}
}
