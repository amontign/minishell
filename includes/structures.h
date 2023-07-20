/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:52:17 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/19 17:13:46 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

//////////////////////////////////////////////////////
//													//
//						 LEXING						//
//													//
//////////////////////////////////////////////////////

# define TOKEN_CMD 1001
# define TOKEN_REDIR 1002
# define TOKEN_PIPE 1003
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
//						   ENV						//
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
//						 LEXING						//
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
//						 EXPAND						//
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
	char		**var_env;
	char		**value_var;
	int			*size_value;
	t_data		*env;
}			t_exp_dol;

//////////////////////////////////////////////////////
//													//
//					  EXECUTION						//
//													//
//////////////////////////////////////////////////////

typedef struct s_cmd_tab
{
	int					id;
	char				*cmd_name;
	char				**args;
	char				*path;
	char				*infile; // null = default
	char				*outfile; // null = default
	int					outfile_delete; // 1 = normal | 0 = ne pas supprimer
	char				*heredoc;
	char				*errfile; // null = default
	struct s_cmd_tab	*prev;
	struct s_cmd_tab	*next;
}						t_cmd_tab;

//////////////////////////////////////////////////////
//													//
//					  SIGNALS						//
//													//
//////////////////////////////////////////////////////

extern int child_process;

#endif