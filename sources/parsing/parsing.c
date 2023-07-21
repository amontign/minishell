/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:39:07 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/21 19:02:03 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dq_spe_char(char c)
{
	if (c == 96 || c == 92)
		return (ft_printf("minishell: '%c' not treated\n", c), TRUE);
	return (FALSE);
}

int	is_metachar(char c)
{
	if (c == '&' || c == ';' || c == 92 || c == '#'
		|| c == '`' || c == '(' || c == ')' || c == 96 || c == '*')
		return (ft_printf("minishell: '%c' not treated\n", c), TRUE);
	return (FALSE);
}

int	closed_quotes(char *cmd_line, int	*i)
{
	if (cmd_line[*i] == SINGLE_QUOTE)
	{
		while (cmd_line[*i] != SINGLE_QUOTE && cmd_line[*i])
			*i += 1;
		if (cmd_line[*i] == '\0')
			return (ft_printf("minishell: unexpected EOF while looking for \
matching `''\nminishell: syntax error: unexpected end of file\n")
				, ERROR_SYNTAX);
		*i += 1;
	}
	if (cmd_line[*i] == DOUBLE_QUOTE)
	{
		while (cmd_line[*i] != DOUBLE_QUOTE)
		{
			if (is_dq_spe_char(cmd_line[*i]) == TRUE)
				return (ERROR_SYNTAX);
			*i += 1;
		}
		if (cmd_line[*i] == '\0')
			return (ft_printf("minishell: unexpected EOF while looking for \
matching `''\nminishell: syntax error: unexpected end of file\n")
				, ERROR_SYNTAX);
		*i += 1;
	}
	return (0);
}

int	untreat_redir(char *cmd_line, int *i)
{
	if (cmd_line[*i] == '>' && cmd_line[*i + 1] == '>'
		&& cmd_line[*i + 2] == '>')
		return (ft_printf("minishell: '>>>' not treated\n"), ERROR_SYNTAX);
	if (cmd_line[*i] == '<' && cmd_line[*i + 1] == '<'
		&& cmd_line[*i + 2] == '<')
		return (ft_printf("minishell: '<<<' not treated\n"), ERROR_SYNTAX);
	return (0);
}

int	pipe_at_end(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	i -= 1;
	while (cmd_line[i] == ' ' || (cmd_line[i] > 6 && cmd_line[i] < 14))
		i--;
	if (cmd_line[i] == '|')
		return (TRUE);
	return (FALSE);
}

int	syntax(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i] == ' ' || (cmd_line[i] > 6 && cmd_line[i] < 14))
	{
		i++;
		if (cmd_line[i] == '|')
			return (ERROR_SYNTAX);
	}
	i = -1;
	while (cmd_line[++i])
	{
		if (closed_quotes(cmd_line, &i) == ERROR_SYNTAX)
			return (ERROR_SYNTAX);
		if (is_metachar(cmd_line[i]) == TRUE)
			return (ERROR_SYNTAX);
		if (cmd_line[i] == '|' && cmd_line[i + 1] == '|')
			return (ft_printf("minishell: '||' not treated\n")
				, ERROR_SYNTAX);
		if (untreat_redir(cmd_line, &i) == ERROR_SYNTAX)
			return (ERROR_SYNTAX);
	}
	if (pipe_at_end(cmd_line) == TRUE)
		return (ft_printf("minishell: syntax error near \
				unexpected token `|'\n"), ERROR_SYNTAX);
	return (0);
}
