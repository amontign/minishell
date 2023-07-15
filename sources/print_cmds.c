/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:45:13 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/11 10:53:17 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_parsing *lexing)
{
	t_parsing	*tmp;
	int			i;
	int			j;

	tmp = lexing;
	while (tmp)
	{
		i = 0;
		ft_printf("\n");
		ft_printf("{ %s } ", tmp->cmd);
		ft_printf("[ %d ] ", tmp->token_type);
		ft_printf("[ %d ] ", tmp->index);
		if (tmp->to_substitute)
		{
			while (tmp->to_substitute[i] >= 0)
			{
				ft_printf("[ $ : %d ]", tmp->to_substitute[i]);
				ft_printf("[ size : %d ]", tmp->dollar_size[i]);
				i++;
			}
		}
		i = 0;
		if (tmp->token_type == TOKEN_CMD && tmp->rmv_qt)
		{
			while (i < ft_strlen_plus(tmp->cmd_split) && tmp->rmv_qt[i])
			{
				j = 0;
				while (i < ft_strlen_plus(tmp->cmd_split) && tmp->rmv_qt[i][j] >= 0)
				{
					ft_printf("[ quote : %d ]", tmp->rmv_qt[i][j]);
					j++;
				}
				i++;
			}
		}
		i = 0;
		if (tmp->token_type == REDIR && tmp->rmv_qt)
		{
			j = 0;
			while (i < 1 && tmp->rmv_qt[i][j] >= 0)
			{
				ft_printf("[ quote : %d ]", tmp->rmv_qt[i][j]);
				j++;
			}
		}
		ft_printf("\n");
		i = 0;
		if (tmp->cmd_split)
		{
			while (tmp->cmd_split[i])
			{
				ft_printf("\narg%d = %s|\n", i, tmp->cmd_split[i]);
				i++;
			}
		}
		tmp = tmp->next;
		ft_printf("\n");
	}
	// tmp = lexing;
	// while (tmp->next)
	// 	tmp = tmp->next;
	// while (tmp)
	// {
	// 	printf("\n");
	// 	printf("{ %s } ", tmp->cmd);
	// 	printf("[ %d ] ", tmp->token_type);
	// 	printf("[ %d ] ", tmp->index);
	// 	tmp = tmp->previous;
	// 	printf("\n");
	// }
	ft_printf("\n");
}
