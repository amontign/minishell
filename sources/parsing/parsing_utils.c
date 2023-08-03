/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:02:15 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 09:03:06 by cbernaze         ###   ########.fr       */
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
