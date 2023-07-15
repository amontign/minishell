/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:30:21 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/08 18:52:26 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

//////////////////////////////////////////////////////
//													//
//						TOKENS						//
//													//
//////////////////////////////////////////////////////

# define TOKEN_CMD 1001
# define TOKEN_REDIR 1002
# define TOKEN_PIPE 1003

//////////////////////////////////////////////////////
//													//
//						BOOLEEN						//
//													//
//////////////////////////////////////////////////////

# define ERROR -1
# define ARG_MAX_MINISH 4095
# define TRUE 10
# define FALSE 11
# define PIPE 20
# define REDIR 21
# define OPENING_QUOTE 30
# define CLOSING_QUOTE 31
# define DOUBLE_QUOTE 34
# define SINGLE_QUOTE 39

//////////////////////////////////////////////////////
//													//
//					   STRUCTURES					//
//													//
//////////////////////////////////////////////////////

typedef struct s_quote
{
	int	quote;
	int	other_quote;
	int	count_quotes;
}		t_quote;

typedef struct s_parsing
{
	char				*cmd;
	char				**cmd_split;
	int					token_type;
	int					size;
	int					index;
	int					*to_substitute;
	int					*dollar_size;
	int					**rmv_qt;
	struct s_parsing	*previous;
	struct s_parsing	*next;
}						t_parsing;

typedef struct s_concatcmd
{
	t_parsing	*to_concat;
	char		*cmd1;
	char		*cmd2;
}			t_concatcmd;

//////////////////////////////////////////////////////
//													//
//						LEXING						//
//													//
//////////////////////////////////////////////////////

t_concatcmd	init_concatcmd(t_parsing *tmp);
void		free_cmds(char **cmd1, char **cmd2);
int			check_empty_cmd(t_parsing **lexing);
t_parsing	*tokenisation(char	*cmd_line);
void		print_cmd(t_parsing *lexing);

//////////////////////////////////////////////////////
//													//
//					   SPLIT_CMD					//
//													//
//////////////////////////////////////////////////////

int			len_cmd(char *cmd_line);
char		*trim_cmd(char	*cmd_line, int *i, int *len);
void		concatenate_cmds(t_parsing **lexing, t_parsing *node);
void		commands_assemble(t_parsing **lexing);
int			split_cmd(t_parsing **lexing, char *cmd_line);

//////////////////////////////////////////////////////
//													//
//					  UTILS LEXING					//
//													//
//////////////////////////////////////////////////////

void		set_index(t_parsing **lexing);
void		is_redir(char *cmd_line, char c, char c_plus_one, int *i);
void		is_redir_2(char *cmd_line, int *i);
int			is_meta(char c, char c_plus_one);
int			which_token_type(char	*cmd);

//////////////////////////////////////////////////////
//													//
//					   UTILS LIST					//
//													//
//////////////////////////////////////////////////////

t_parsing	*ft_lstnew_minishell(char *str, int size_str, int type);
void		ft_lstclear_minishell(t_parsing **lexing);
void		clear_node(t_parsing **node);
void		ft_lstadd_back_minishell(t_parsing **lexing, t_parsing *new);
void		swap_nodes(t_parsing **lexing);
void		free_quotes(t_parsing *lexing);

//////////////////////////////////////////////////////
//													//
//						MAIN						//
//													//
//////////////////////////////////////////////////////

void		remove_newline(char **name_eval);

#endif
