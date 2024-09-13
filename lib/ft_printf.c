/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:02:30 by mjameau           #+#    #+#             */
/*   Updated: 2024/06/18 11:19:47 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_format(va_list ap, const char format)
{
	int	i;

	i = 0;
	if (format == 'c')
		i += ft_print_c(va_arg(ap, int));
	else if (format == 's')
		i += ft_print_s(va_arg(ap, char *));
	else if (format == 'p')
		i += ft_print_p(va_arg(ap, void *));
	else if (format == 'd')
		i += ft_print_di(va_arg(ap, int));
	else if (format == 'i')
		i += ft_print_di(va_arg(ap, int));
	else if (format == 'u')
		i += ft_print_u(va_arg(ap, unsigned int));
	else if (format == 'x')
		i += ft_print_xx(va_arg(ap, unsigned int), format);
	else if (format == 'X')
		i += ft_print_xx(va_arg(ap, unsigned int), format);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	unsigned int	i;

	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_strchr("cspdiuxX", *format))
				i += check_format(ap, *format);
			else if (*format == '%')
				i += ft_print_c('%');
		}
		else
			i = i + ft_print_c(*format);
		format++;
	}
	va_end(ap);
	return (i);
}
