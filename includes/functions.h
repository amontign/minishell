/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:56:11 by cbernaze          #+#    #+#             */
/*   Updated: 2023/08/03 08:34:43 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"
# include "libft.h"

/*parsing.c*/

int			is_dq_spe_char(char c);
int			is_metachar(char c);
int			closed_quotes(char *cmd_line, int	*i);
int			untreat_redir(char *cmd_line, int *i);
int			pipe_at_end(char *cmd_line);
int			pipe_at_start(char *cmd_line);
int			syntax(char *cmd_line);
int			wrong_after_redir(char *cmd_line, int *i);
void		final_parsing(t_parsing **lexing, t_data **env);

//////////////////////////////////////////////////////
//													//
//						LEXING						//
//													//
//////////////////////////////////////////////////////

/*lexing.c*/

t_concatcmd	init_concatcmd(t_parsing *tmp);
void		free_cmds(char **cmd1, char **cmd2);
int			check_empty_cmd(t_parsing **lexing);
t_parsing	*tokenisation(char	*cmd_line);
void		print_cmd(t_parsing *lexing);

/*split_cmd.c*/

int			len_cmd(char *cmd_line);
char		*trim_cmd(char	*cmd_line, int *i, int *len);
void		concatenate_cmds(t_parsing **lexing, t_parsing *node);
void		commands_assemble(t_parsing **lexing);
int			split_cmd(t_parsing **lexing, char *cmd_line);

/*utils_lexing.c*/

void		set_index(t_parsing **lexing);
void		is_redir(char *cmd_line, char c, char c_plus_one, int *i);
void		is_redir_2(char *cmd_line, int *i);
void		is_redir_3(char *cmd_line, int *i);
int			is_meta(char c, char c_plus_one);
int			which_token_type(char	*cmd);

/*utils_list.c*/

t_parsing	*ft_lstnew_minishell(char *str, int size_str, int type);
void		ft_lstclear_minishell(t_parsing **lexing);
void		clear_node(t_parsing **node);
void		ft_lstadd_back_minishell(t_parsing **lexing, t_parsing *new);
void		free_quotes(t_parsing *lexing);

/*main.c*/

void		remove_newline(char **name_eval);

//////////////////////////////////////////////////////
//													//
//						EXPAND						//
//													//
//////////////////////////////////////////////////////

/*expand.c*/

int			ft_isalnum_env(int c);
char		*remove_cmd_quotes(t_data_qt *dt);
void		how_many_cmd_quotes_3(char *arg, int *i, int *quotes);
void		expand(t_parsing **expand, t_data *env);

/*pre_expand_dollars.c*/

int			pre_expand_dollar(t_parsing **exp_dollar);
int			pre_expand_dollar_2(t_parsing **tmp, int *i, int tab);
int			pre_expand_dollar_3(t_parsing **tmp, int *i, int choice, int *tab);
void		pre_expand_dollar_4(t_parsing **tmp, int *i, int choice);
int			pre_expand_dollar_5(t_parsing **tmp, int *i, int choice, int *tab);

/*utils_pre_expand_dollars.c*/

int			am_a_lonesome_dollar(char *cmd, int dollar_pos, int choice);
int			how_many_dollars(t_parsing **tmp);
void		how_many_dollars_2(t_parsing **tmp, int *i, int *size_subt_tab);
char		*remove_dollar(char *str, int dol_pos);
int			i_need_a_dollar(t_parsing **tmp, int dol_pos, int choice, int *tab);

/*expand_dollars.c*/

int			expand_dollars(t_parsing **expand, t_data *env);
char		*substitute_dollars(t_parsing **tmp, t_data *env, int nb_dol);
void		subst_dols_2(char **new, t_exp_dol data, t_parsing **tmp, int tab);
void		subst_dollars_3(t_exp_dol *data, int tab, char **new);
int			f_dt_dol(t_exp_dol *data, t_data *env, t_parsing *tmp, int nb_dol);
int			fill_data_dol_2(t_exp_dol *data, t_parsing *tmp, int *j, int tab);
void		fill_data_dol_3(t_exp_dol *data, int tab);

/*utils_expand_dollars.c*/

int			malloc_data_strs(t_exp_dol *data, int nb_dol);
void		free_data(t_exp_dol	*data);
void		go_through_quotes(char *str, int *i);
char		*getenv_minish(t_data *data, char *var);
int			ft_isalnum_dol(int c, int pos);

/*split_args.c*/

void		arg_count(t_parsing *tmp, int *nb_arg);
int			len_arg(char *str);
int			create_arg(char *str, char ***split, int *i, int *j);
int			trim_args(t_parsing **tmp);
int			split_args(t_parsing **expand);

/*expand_cmd_quotes.c*/

int			expand_cmd_quotes(t_parsing **expand);
void		expand_cmd_quotes_2(t_parsing **tmp, t_data_qt *dt, char *arg);
void		expand_cmd_quotes_3(t_parsing **tmp, t_data_qt *dt, char *arg);
int			how_many_cmd_quotes(t_parsing **tmp);
int			how_many_cmd_quotes_2(t_parsing **tmp, int tab);

/*expand_redir_quotes.c*/

int			expand_redir_quotes(t_parsing **expand);
void		expand_redir_quotes_2(t_parsing **tmp, int *i, int *j);
int			how_many_redir_quotes(t_parsing **tmp);
void		how_many_redir_quotes_2(t_parsing **tmp, int *i, int *size_tab);
char		*rmv_redir_quotes(char *str, int *quote_pos);

//////////////////////////////////////////////////////
//													//
//						 GETENV						//
//													//
//////////////////////////////////////////////////////

/*create_env.c*/

int			create_env(t_data **data);
int			create_env_2(t_data **data, char *pwd);
int			ft_getenv(t_data **data, char **envp);

/*utils_create_env.c*/

t_data		*ft_lstnew_data(char *var_env);
void		ft_lstadd_back_data(t_data **data, t_data *new);
void		ft_lstclear_data(t_data **data);

//////////////////////////////////////////////////////
//													//
//						BUILTINS					//
//													//
//////////////////////////////////////////////////////

/*echo.c*/

int			ft_strcmp_minishell(char *s1, char *s2);
char		**newline_terminated(char **echo, int size_echo);
int			builtin_echo(char **echo, int fd);

/*cd.c*/

int			builtin_cd(char **dir_name, t_data *env, t_cmd_tab *current);

/*unset.c*/

void		remove_env_var(t_data *tmp);
void		unset_2(t_data **data, t_data *next, t_data *tmp, char **to_unset);
int			unset(t_data **data, char **to_unset, t_cmd_tab *current);

/*pwd.c*/

int			builtin_pwd(char **args, int fd);

/*exit.c*/

int			builtin_exit(char **args, t_norm_exec *normy, t_cmd_tab *current);
int			command_only_e(t_cmd_tab *current);

/*env.c*/

int			builtin_env(char **args, t_data *env, int fd);

/*export.c*/

int			arg_zero_is_nb(int fd, char *arg);
int			arg_is_valid(char *arg, int fd);
int			export(char **args, t_data *env, int fd, t_cmd_tab *current);

//////////////////////////////////////////////////////
//													//
//					  EXECUTION						//
//													//
//////////////////////////////////////////////////////

/*cmd_to_struct.c*/

int			find_place_path(t_cmd_tab **cmd_struct, t_data *env);
void		lexing_to_cmd_tab(t_parsing *lexing, t_cmd_tab **c, t_data *env);

/*execution_utils.c*/

void		free_char_tab(char **tab);
void		print_node_content(void *arg);
char		**str_tab_dup(char **str_tab);
void		free_cmd_struct(t_cmd_tab **cmd_struct);

/*main_execution.c*/

void		change_status(t_data *env, int status);
int			prompt_execution(t_parsing **lexing, t_data **env);
int			in_builtin(char *cmd);
void		change_status(t_data *env, int status);
char		**env_to_tab(t_data *env);

/*cmd_struct_utils.c*/

t_cmd_tab	*cmd_struct_last(t_cmd_tab *lst);
void		cmd_struct_add_back(t_cmd_tab **lst, t_cmd_tab *new);
t_cmd_tab	*cmd_struct_new(char **args, void *content2, int id);
void		cmd_struct_iter(t_cmd_tab *lst, void (*f)(void *));

/*main_signals.c*/

void		main_signal(void);

#endif
