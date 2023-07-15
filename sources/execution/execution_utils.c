/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:25 by amontign          #+#    #+#             */
/*   Updated: 2023/07/15 15:44:19 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_node_content(void *arg)
{
	t_cmd_tab	*node;
	int			i;

	i = 1;
	node = (t_cmd_tab *)arg;
	printf("Id           : %d\n", (int)node->id);
	printf("Command Name : %s\n", (char *)node->cmd_name);
	while (node->args[i])
	{
		printf("Arg %d        : %s\n", i, (char *)node->args[i]);
		i++;
	}
	printf("Path         : %s\n", (char *)node->path);
	printf("Infile       : %s\n", (char *)node->infile);
	printf("Outfile      : %s\n", (char *)node->outfile);
	printf("Errfile      : %s\n", (char *)node->errfile);
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
