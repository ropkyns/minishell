/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:05:30 by paulmart          #+#    #+#             */
/*   Updated: 2024/09/30 16:20:28 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_syntaxe(char *value)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, value, ft_strlen(value));
	write(2, "'\n", 2);
}
