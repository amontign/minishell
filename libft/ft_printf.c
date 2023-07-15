/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernaze <cbernaze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:35:09 by cbernaze          #+#    #+#             */
/*   Updated: 2023/04/25 17:37:05 by cbernaze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_conversions(char c, va_list ap, int len)
{
	if (c == 'c')
		len += ft_putchar_fd(va_arg(ap, int), 1);
	if (c == 's')
		len += ft_putstr_fd(va_arg(ap, const char *), 1);
	if (c == 'p')
		len += ft_putvoid_fd(va_arg(ap, unsigned long long int),
				"0123456789abcdef", 1);
	if (c == 'd' || c == 'i')
		len += ft_putnbr_fd(va_arg(ap, int), 1);
	if (c == 'u')
		len += ft_put_unsigned_nbr_fd(va_arg(ap, unsigned int), 1);
	if (c == 'x')
		len += ft_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789abcdef", 1);
	if (c == 'X')
		len += ft_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789ABCDEF", 1);
	if (c == '%')
		len += ft_putchar_fd('%', 1);
	return (len);
}

int	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (0);
	else
		return (1);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start(ap, str);
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (is_specifier(str[i + 1]) == 0)
			{
				len += ft_conversions(str[i + 1], ap, 0);
				i++;
			}
		}
		else
			len += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}
