/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:30:06 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/09 15:53:59 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

//////////////////////////////////////////////////////
//													//
//					   STRUCTURES					//
//													//
//////////////////////////////////////////////////////

typedef struct s_data
{
	char			*var;
	int				len;
	struct s_data	*previous;
	struct s_data	*next;
}					t_data;

//////////////////////////////////////////////////////
//													//
//						 GETENV						//
//													//
//////////////////////////////////////////////////////

t_data	*ft_lstnew_data(char *var_env);
void	ft_lstadd_back_data(t_data **data, t_data *new);
void	ft_lstclear_data(t_data **data);
int		create_env(t_data **data);
int		create_env_2(t_data **data, char *pwd);
int		ft_getenv(t_data **data, char **envp);

#endif