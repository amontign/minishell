/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:59:25 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 08:23:17 by cbernaze         ###   ########.fr       */
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
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**str_tab_dup(char **str_tab)
{
	char	**new_str_tab;
	int		i;

	i = 0;
	while (str_tab[i])
	{
		i++;
	}
	new_str_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_str_tab)
		exit(1);
	i = 0;
	while (str_tab[i])
	{
		new_str_tab[i] = ft_strdup(str_tab[i]);
		i++;
	}
	new_str_tab[i] = NULL;
	return (new_str_tab);
}

void	free_cmd_struct(t_cmd_tab **cmd_struct)
{
	t_cmd_tab *current = *cmd_struct;
	t_cmd_tab *next_node;

	while (current != NULL)
	{
		next_node = current->next;
		if (current->heredoc)
		{
			free(current->heredoc);
		}
		free(current->cmd_name);
		free(current->path);
		free(current);
		current = next_node;
	}
	*cmd_struct = NULL;
}
