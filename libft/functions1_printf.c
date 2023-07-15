/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:30:00 by cbernaze          #+#    #+#             */
/*   Updated: 2023/07/01 12:21:56 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", 1));
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		len += len + 11;
	}
	if (n < 0 && n != -2147483648)
	{
		write(fd, "-", 1);
		n *= -1;
		len += len + 1;
	}
	if (n >= 0 && n <= 9)
	{
		len += ft_putchar_fd(n + '0', fd);
	}
	if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	return (len);
}

int	ft_put_unsigned_nbr_fd(unsigned int n, int fd)
{
	int	len;

	len = 0;
	if (n <= 9)
	{
		len += ft_putchar_fd(n + '0', fd);
	}
	if (n > 9)
	{
		len += ft_putnbr_fd(n / 10, fd);
		len += ft_putnbr_fd(n % 10, fd);
	}
	return (len);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
		i++;
	return (i);
}
