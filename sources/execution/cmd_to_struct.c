/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:41:01 by amontign          #+#    #+#             */
/*   Updated: 2023/07/26 10:30:23 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	custom_path(t_cmd_tab *cmd_struct)
{
	int		i;
	char	*tmp;

	if (!cmd_struct->cmd_name)
		return (0);
	i = ft_strlen(cmd_struct->cmd_name) - 1;
	while (cmd_struct->cmd_name[i] && cmd_struct->cmd_name[i] != '/')
		i--;
	if (i == -1)
		return (0);
	tmp = ft_strdup(cmd_struct->cmd_name);
	free(cmd_struct->cmd_name);
	cmd_struct->cmd_name = ft_strdup(tmp + i + 1);
	cmd_struct->path = ft_strdup(tmp);
	free(tmp);
	if (access(cmd_struct->path, F_OK) == 0)
		return (1);
	else
		return (0);
}

int	place_path(char **paths, t_cmd_tab *cmd_struct)
{
	int		i;
	char	*path;
	char	*path2;

	while (cmd_struct)
	{
		i = -1;
		while (paths[++i] && !cmd_struct->path && cmd_struct->cmd_name)
		{
			path = ft_strjoin(paths[i], "/");
			if (!path)
				return (0);
			path2 = ft_strjoin(path, cmd_struct->cmd_name);
			free(path);
			if (!path2)
				return (0);
			if (access(path2, F_OK) == 0)
				cmd_struct->path = ft_strdup(path2);
			free(path2);
		}
		if (!cmd_struct->path && !custom_path(cmd_struct) && !in_builtin(cmd_struct->cmd_name))
			return (0);
		cmd_struct = cmd_struct->next;
	}
	return (1);
}

int	find_place_path(t_cmd_tab **cmd_struct, t_data *env)
{
	char	**paths;

	paths = NULL;
	while (env)
	{
		if (ft_strnstr(env->var, "PATH", 4) != 0)
		{
			paths = ft_split((env->var + 5), ':');
			break ;
		}
		env = env->next;
	}
	if (!paths)
		return (0);
	if (!place_path(paths, *cmd_struct))
	{
		free_char_tab(paths);
		return (0);
	}
	free_char_tab(paths);
	return (1);
}

int	c_r_s(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '>' || str[i] == '<' || (str[i] > 8 && str[i] < 14)
		|| str[i] == ' ')
	{
		i++;
	}
	return (i);
}

char	*heredoc_complete(char *str)
{
	char	*res;
	char	*res2;
	char	*current_line;
	int		diff;

	current_line = readline(">");
	res = ft_strdup("");
	diff = ft_strcmp(current_line, str);
	while (diff != 0)
	{
		if (!current_line)
			return (printf("warning: end-of-file detected in heredoc\n"), res);
		res2 = ft_strjoin(res, current_line);
		free(current_line);
		free(res);
		res = ft_strjoin(res2, "\n");
		free(res2);
		current_line = readline(">");
		diff = ft_strcmp(current_line, str);
	}
	free(current_line);
	return (res);
}

int	put_redirect(t_cmd_tab *cmd_struct, char *str, int id)
{
	t_cmd_tab	*first;

	first = cmd_struct;
	if (!str || !str[0] || !str[1] || !str[2])
		return (2);
	while (first)
	{
		if (first->id == id)
			break ;
		first = first->next;
	}
	if (str[0] == '>')
	{
		if (str[1] == '>')
			first->outfile_delete = 0;
		first->outfile = str + c_r_s(str);
	}
	else
	{
		if (str[1] == '<')
			first->heredoc = heredoc_complete(str + c_r_s(str));
		else
			first->infile = str + c_r_s(str);
	}
	return (1);
}

void	put_redirects(t_parsing *lexing, t_cmd_tab **cmd_struct)
{
	t_parsing	*lexing2;
	int			id;
	int			put_r;

	id = 0;
	while (lexing)
	{
		if (lexing->token_type == TOKEN_CMD)
			id++;
		else if (lexing->token_type == TOKEN_REDIR)
		{
			put_r = 0;
			lexing2 = lexing;
			while (lexing2 && lexing2->token_type != TOKEN_PIPE)
			{
				if (lexing2->token_type == TOKEN_CMD)
					put_r = put_redirect(*cmd_struct, lexing->cmd, (id - 1));
				lexing2 = lexing2->previous;
			}
			if (put_r == 0)
				put_redirect(*cmd_struct, lexing->cmd, id);
		}
		lexing = lexing->next;
	}
}

void	lexing_to_cmd_tab(t_parsing *lexing, t_cmd_tab **cmd_struct)
{
	int			id;
	t_parsing	*lexing_start;

	id = 0;
	lexing_start = lexing;
	while (lexing)
	{
		if (lexing->token_type == TOKEN_CMD)
		{
			cmd_struct_add_back(cmd_struct,
				cmd_struct_new(lexing->cmd_split,
					ft_strdup(lexing->cmd_split[0]), id));
			id++;
		}
		lexing = lexing->next;
	}
	put_redirects(lexing_start, cmd_struct);
}
