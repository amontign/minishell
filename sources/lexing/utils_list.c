/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:02:45 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/11 10:56:21 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Creer un nouveau maillon pour les listes chainees de type t_parsing*/

t_parsing	*ft_lstnew_minishell(char *str, int size_str, int type)
{
	t_parsing	*new;
	int			i;

	if (!str)
		return (NULL);
	new = malloc(sizeof(t_parsing));
	if (!new)
		return (ft_printf("minishell: malloc error\n"), NULL);
	new->cmd = malloc((size_str + 1) * sizeof(char));
	if (!new->cmd)
		return (ft_printf("minishell: malloc error\n"), free(new), NULL);
	i = -1;
	while (str[++i])
		new->cmd[i] = str[i];
	new->cmd[i] = '\0';
	new->cmd_split = NULL;
	new->token_type = type;
	new->size = size_str;
	new->index = 0;
	new->to_substitute = NULL;
	new->dollar_size = NULL;
	new->rmv_qt = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

/*Detruit une liste chaine de type t_parsing*/

void	ft_lstclear_minishell(t_parsing **lexing)
{
	t_parsing	*tmp;
	int			i;

	if (!(*lexing) || !lexing)
		return ;
	while (*lexing)
	{
		tmp = (*lexing)->next;
		free_quotes(*lexing);
		if (ft_strcmp_minishell((*lexing)->cmd, "error") == FALSE)
			free((*lexing)->cmd);
		if ((*lexing)->cmd_split)
		{
			i = -1;
			while ((*lexing)->cmd_split[++i])
				free((*lexing)->cmd_split[i]);
			free((*lexing)->cmd_split);
		}
		if ((*lexing)->dollar_size)
			free((*lexing)->dollar_size);
		free((*lexing)->to_substitute);
		free(*lexing);
		(*lexing) = tmp;
	}
	*lexing = NULL;
}

void	free_quotes(t_parsing *lexing)
{
	int	i;

	i = 0;
	if (lexing->rmv_qt)
	{
		while (lexing->rmv_qt[i])
		{
			free(lexing->rmv_qt[i]);
			i++;
		}
		free(lexing->rmv_qt);
		lexing->rmv_qt = NULL;
	}
}

/*Detruit un maillon pour les listes chainees de type t_parsing*/

void	clear_node(t_parsing **node)
{
	(*node)->next = NULL;
	(*node)->previous = NULL;
	if ((*node)->cmd_split)
		free((*node)->cmd_split);
	free(*node);
	*node = NULL;
}

/*Ajouter un nouveau maillon a la fin d'une liste
pour les listes chainees de type t_parsing*/

void	ft_lstadd_back_minishell(t_parsing **lexing, t_parsing *new)
{
	t_parsing	*tmp;

	tmp = *lexing;
	if (*lexing && lexing)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->previous = tmp;
		tmp->next = new;
	}
	else
		*lexing = new;
}
