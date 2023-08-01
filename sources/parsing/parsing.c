/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:39:07 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/01 11:22:40 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*This function looks for untreated metachar inside double quotes.*/

int	is_dq_spe_char(char c)
{
	if (c == 96 || c == 92)
		return (ft_printf("minishell: '%c' not treated\n", c), TRUE);
	return (FALSE);
}

/*This function looks for uyntreated metachars.*/

int	is_metachar(char c)
{
	if (c == '&' || c == ';' || c == 92 || c == '#'
		|| c == '`' || c == '(' || c == ')' || c == 96 || c == '*')
		return (ft_printf("minishell: '%c' not treated\n", c), TRUE);
	return (FALSE);
}

/*This function checks if all quotes are closed.*/

int	closed_quotes(char *cmd_line, int	*i)
{
	if (cmd_line[*i] == SINGLE_QUOTE)
	{
		*i += 1;
		while (cmd_line[*i] != SINGLE_QUOTE && cmd_line[*i])
			*i += 1;
		if (cmd_line[*i] == '\0')
			return (ft_printf("minishell: unexpected EOF while looking for \
matching `''\nminishell: syntax error: unexpected end of file\n")
				, ERROR_SYNTAX);
	}
	if (cmd_line[*i] == DOUBLE_QUOTE)
	{
		*i += 1;
		while (cmd_line[*i] != DOUBLE_QUOTE && cmd_line[*i])
			*i += 1;
		if (cmd_line[*i] == '\0')
			return (ft_printf("minishell: unexpected EOF while looking for \
matching `\"'\nminishell: syntax error: unexpected end of file\n")
				, ERROR_SYNTAX);
	}
	return (0);
}

/*This function checks if a pipe doesn't end a command line.*/

int	pipe_at_end(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i])
		i++;
	i -= 1;
	while (i > 0 && cmd_line[i] && (cmd_line[i] == ' ' || (cmd_line[i] > 8 && cmd_line[i] < 14)))
		i--;
	if (i > 0 && cmd_line[i] == '|')
		return (TRUE);
	return (FALSE);
}

/*This function checks if a command line doesn't begin with a pipe.*/

int	pipe_at_start(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i] && (cmd_line[i] == ' '
			|| (cmd_line[i] > 8 && cmd_line[i] < 14)))
		i++;
	if (cmd_line[i] == '|' && cmd_line[i + 1] == '|')
		return (ft_printf("minishell: syntax error near \
unexpected token `||'\n"), ERROR_SYNTAX);
	if (cmd_line[i] == '|')
		return (ft_printf("minishell: syntax error near \
unexpected token `|'\n"), ERROR_SYNTAX);
	return (0);
}

/*This function goes through the command line and
launches different syntax checks.*/

int	syntax(char *cmd_line)
{
	int	i;

	if (pipe_at_start(cmd_line) == ERROR_SYNTAX)
		return (ERROR_SYNTAX);
	i = 0;
	while (cmd_line[i])
	{
		if (closed_quotes(cmd_line, &i) == ERROR_SYNTAX)
			return (ERROR_SYNTAX);
		if (cmd_line[i] == '|' && cmd_line[i + 1] == '|')
			return (ft_printf("minishell: '||' not treated\n")
				, ERROR_SYNTAX);
		if (cmd_line[i] == '<' || cmd_line[i] == '>')
		{
			if (wrong_after_redir(cmd_line, &i) == ERROR_SYNTAX)
				return (ERROR_SYNTAX);
			else
				i--;
		}
		i++;
	}
	if (pipe_at_end(cmd_line) == TRUE)
		return (ft_printf("minishell: syntax error near \
unexpected token `|'\n"), ERROR_SYNTAX);
	return (0);
}

/*This function checks that redirections are correctly written.*/

int	wrong_after_redir(char *cmd_line, int *i)
{
	if (cmd_line[*i] && cmd_line[*i] == '>' && cmd_line[*i + 1] == '<')
		return (ft_printf("minishell: syntax error near \
unexpected token `%c'\n", cmd_line[*i + 1]), ERROR_SYNTAX);
	else
		*i += 1;
	if (cmd_line[*i] && (cmd_line[*i] == '<' || cmd_line[*i] == '>'))
		*i += 1;
	while (cmd_line[*i] && (cmd_line[*i] == ' '
			|| (cmd_line[*i] > 8 && cmd_line[*i] < 14)))
		*i += 1;
	if (cmd_line[*i] == '\0')
		return (ft_printf("minishell: syntax error near \
unexpected token `newline'\n"), ERROR_SYNTAX);
	if (((cmd_line[*i] == '<' && cmd_line[*i + 1] == '<'))
		|| ((cmd_line[*i] == '>' && cmd_line[*i + 1] == '>')))
		return (ft_printf("minishell: syntax error near \
unexpected token `%c%c'\n", cmd_line[*i], cmd_line[*i + 1]), ERROR_SYNTAX);
	if (cmd_line[*i] == '<' || cmd_line[*i] == '>' || cmd_line[*i] == '|')
		return (ft_printf("minishell: syntax error near \
unexpected token `%c'\n", cmd_line[*i]), ERROR_SYNTAX);
	return (0);
}

/*This functions verifies that two pipe tokens are next to each other.*/

void	final_parsing(t_parsing **lexing, t_data **env)
{
	t_parsing	*tmp;

	tmp = *lexing;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_PIPE)
		{
			if (tmp->next->token_type == TOKEN_PIPE)
			{
				ft_printf("minishell: syntax error near \
unexpected token `|'\n");
				ft_lstclear_minishell(lexing);
				change_status(*env, 2);
				return ;
			}
		}
		tmp = tmp->next;
	}
}
