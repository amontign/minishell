/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:34:13 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/27 15:24:37 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Fonction qui s'assure de la presence de '\n' a la fin des parametres
de echo s'il y en a un on ne fait rien, sinon on en rajoute un*/

int	ft_strcmp_minishell(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (ERROR);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	**newline_terminated(char **echo, int size_echo)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i < size_echo - 1)
		i++;
	while (echo[i][j])
		j++;
	if (echo[i][j - 1] != '\n')
	{
		tmp = echo[i];
		echo[i] = ft_strjoin(echo[i], "\n");
		free(tmp);
	}
	return (echo);
}

/*Builtin de la commande echo*/

int	builtin_echo(char **echo, int fd)
{
	int	i;
	int	size_echo;

	i = 1;
	size_echo = ft_strlen_plus(echo) - 1;
	echo = newline_terminated(echo, size_echo + 1);
	if (!echo[1])
		ft_putchar_fd('\n', fd);
	if (ft_strcmp_minishell(echo[1], "-n") == TRUE)
	{
		while (i < (size_echo))
			i++;
		remove_newline(echo + i);
		i = 2;
	}
	while (echo[i])
	{
		ft_putstr_fd(echo[i], fd);
		if (i != size_echo)
			ft_putchar_fd(' ', fd);
		i++;
	}
	return (0);
}

// int	main()
// {
// 	char	*cmd_line;

// 	while (42)
// 	{
// 		ft_printf("minishell> ");
// 		cmd_line = get_next_line(0);
// 		builtin_echo(ft_split(cmd_line, ' '));
// 	}
// 	return (0);
// }