/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:45:23 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/10 12:06:54 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

//////////////////////////////////////////////////////
//													//
//					   STRUCTURES					//
//													//
//////////////////////////////////////////////////////

typedef struct s_data_qt
{
	t_parsing	*tmp;
	int			nb_quotes;
	int			i;
	int			j;
	int			k;
}				t_data_qt;

typedef struct s_exp_dol
{
	char	**var_env;
	char	**value_var;
	int		*size_value;
}			t_exp_dol;

//////////////////////////////////////////////////////
//													//
//						EXPAND						//
//													//
//////////////////////////////////////////////////////

int			pre_expand_dollar(t_parsing **exp_dollar);
int			pre_expand_dollar_2(t_parsing **tmp, int *i, int choice, int *tab);
void		pre_expand_dollar_3(t_parsing **tmp, int *i, int choice);
int			pre_expand_dollar_4(t_parsing **tmp, int *i, int choice, int *tab);
void		expand(t_parsing **expand);

//////////////////////////////////////////////////////
//													//
//				UTILS PRE EXPAND DOLLAR				//
//													//
//////////////////////////////////////////////////////

int			am_a_lonesome_dollar(char *cmd, int dollar_pos);
int			how_many_dollars(t_parsing **tmp);
void		how_many_dollars_2(t_parsing **tmp, int *i, int *size_subt_tab);
char		*remove_dollar(char *str, int dol_pos);
int			i_need_a_dollar(t_parsing **tmp, int dol_pos, int choice, int *tab);

//////////////////////////////////////////////////////
//													//
//					EXPAND DOLLARS					//
//													//
//////////////////////////////////////////////////////

int			expand_dollars(t_parsing **expand);
char		*substitute_dollars(t_parsing **tmp, int nb_dol);
void		substitute_dollars_2(char **new, t_exp_dol data, t_parsing **tmp);
int			fill_data_dol(t_exp_dol *data, t_parsing *tmp, int nb_dol);
int			fill_data_dol_2(t_exp_dol *data, t_parsing *tmp, int *j, int tab);

//////////////////////////////////////////////////////
//													//
//				  UTILS EXPAND DOLLAR				//
//													//
//////////////////////////////////////////////////////

int			malloc_data_strs(t_exp_dol *data, int nb_dol);
void		free_data(t_exp_dol	*data);
void		go_through_quotes(char *str, int *i);

//////////////////////////////////////////////////////
//													//
//					  SPLIT ARGS					//
//													//
//////////////////////////////////////////////////////

void		arg_count(t_parsing *tmp, int *nb_arg);
int			len_arg(char *str);
int			create_arg(char *str, char ***split, int *i, int *j);
int			trim_args(t_parsing **tmp);
int			split_args(t_parsing **expand);

//////////////////////////////////////////////////////
//													//
//					EXPAND CMD QUOTES				//
//													//
//////////////////////////////////////////////////////

int			expand_cmd_quotes(t_parsing **expand);
void		expand_cmd_quotes_2(t_parsing **tmp, t_data_qt *dt, char *arg);
void		expand_cmd_quotes_3(t_parsing **tmp, t_data_qt *dt, char *arg);
int			how_many_cmd_quotes(t_parsing **tmp);
int			how_many_cmd_quotes_2(t_parsing **tmp, int tab);
void		how_many_cmd_quotes_3(char *arg, int *i, int *quotes);
char		*remove_cmd_quotes(t_data_qt dt);

//////////////////////////////////////////////////////
//													//
//					EXPAND REDIR QUOTES				//
//													//
//////////////////////////////////////////////////////

int			expand_redir_quotes(t_parsing **expand);
void		expand_redir_quotes_2(t_parsing **tmp, int *i, int *j);
int			how_many_redir_quotes(t_parsing **tmp);
void		how_many_redir_quotes_2(t_parsing **tmp, int *i, int *size_tab);
char		*rmv_redir_quotes(char *str, int *quote_pos);

#endif