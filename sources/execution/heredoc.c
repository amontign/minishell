/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:05:28 by amontign          #+#    #+#             */
/*   Updated: 2023/08/03 09:08:46 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*var_value(t_data *env, char *str)
{
	char	*str_equal;
	char	*return_str;

	str_equal = ft_strjoin(str, "=");
	free(str);
	while (env)
	{
		if (ft_strncmp(env->var, str_equal, ft_strlen(str_equal)) == 0)
		{
			return_str = ft_strdup(env->var + ft_strlen(str_equal));
			free(str_equal);
			return (return_str);
		}
		env = env->next;
	}
	free(str_equal);
	return (ft_strdup(""));
}

char	*extract_var_name(const char *str, int *i)
{
	char	varname[256];
	int		varlen;

	varlen = 0;
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\0'
		&& str[*i] != '$')
		varname[varlen++] = str[(*i)++];
	varname[varlen] = '\0';
	return (ft_strdup(varname));
}

char	*expand_var(char *result, int *j, const char *value)
{
	int		len;
	int		i;
	int		k;
	char	*ret;

	i = 0;
	k = 0;
	len = ft_strlen(value);
	ret = malloc(sizeof(char) * (*j + len + 1));
	while (i < *j)
	{
		ret[i] = result[i];
		i++;
	}
	while (value[k])
	{
		ret[i + k] = value[k];
		k++;
	}
	ret[i + k] = '\0';
	free(result);
	*j += len;
	return (ret);
}

char	*expand_heredoc(char *str, t_data *env)
{
	int		i;
	int		j;
	char	*result;
	char	*varname;
	char	*value;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	result[0] = '\0';
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			varname = extract_var_name(str, &i);
			value = var_value(env, varname);
			result = expand_var(result, &j, value);
			free(value);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (free(str), result);
}

char	*heredoc_complete(char *str, t_data *env)
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
		current_line = expand_heredoc(current_line, env);
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
