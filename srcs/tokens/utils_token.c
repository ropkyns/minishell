/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulmart <paulmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:23:36 by mjameau           #+#    #+#             */
/*   Updated: 2024/09/23 16:14:55 by paulmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Check si whitespace ou space
 */
bool	is_space(char c)
{
	if ((c && (c >= 9 && c <= 13)) || (c == ' '))
		return (true);
	return (false);
}

/*
 * Check si caractere special (operateur), on return le enum
 */
int	is_special(char *token)
{
	if (token && *token && ft_strlen(token) >= 2)
	{
		if (!ft_strncmp(token, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(token, ">>", 2))
			return (APPEND);
	}
	if (token && *token && ft_strlen(token) >= 1)
	{
		if (!ft_strncmp(token, ">", 1))
			return (OUTPUT);
		if (!ft_strncmp(token, "<", 1))
			return (INPUT);
		if (!ft_strncmp(token, "|", 1))
			return (PIPE);
	}
	return (0);
}

/*
* On free tout les tokens, on copie le 1er element de la liste dans curr
ensuite on va parcourir tout les tokens dont le ->next ne pointe pas sur le
premier element de la liste. (En gros tous sauf le dernier)
On prend les element dans temp et on free (+ simple pour le premier)
ensuite une fois la boucle finie on free le dernier element.
On free la value (str) d'abord parce que on l'a mit avec strdup
*/
void	free_tok(t_structok **token_list)
{
	t_structok	*curr;
	t_structok	*temp;

	if (!*token_list)
		return ;
	curr = *token_list;
	while (curr->next != *token_list)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp);
	}
	free(curr->value);
	free(curr);
	*token_list = NULL;
}

/*
* Ici on calcule la taille de la ligne de commande et le le nombre de quote
(on compte que la 1ere quote car on fait *2 dans la fonction add_cmd_arg)
*/
int	len_cmd(char *command, int *quote)
{
	int	i;

	i = 0;
	*quote = 0;
	while (command[i] && !is_space(command[i]) && !is_special(command + i))
	{
		if (command[i] == '"' || command[i] == '\'')
		{
			(*quote)++;
			if (command[i++] == '"')
				while (command[i] && command[i] != '"')
					++i;
			else
				while (command[i] && command[i] != '\'')
					++i;
			if (command[i])
				++i;
		}
		if (command[i] && command[i] != '"' && command[i] != '\''
			&& !is_space(command[i]) && !is_special(command + i))
			++i;
		// i++;
	}
	return (i);
}

/*
* Cette fonction sert a prendre la ligne de commande et de recuperer
ce qu'il y a entre les quotes dans str avec un decalage de -1 pour ne pas
copier les quotes (' et "),sinon sans decalage
*/
void	get_words_to_token(char *command, int len, char *str, int i)
{
	int	j;

	j = 0;
	while (command[i + j] && i < len)
	{
		if (command[i + j] == '\'' && ++j)
		{
			while (command[i + j] != '\'' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else if (command[i + j] == '"' && ++j)
		{
			while (command[i + j] != '"' && ++i)
				str[i - 1] = command[(i - 1) + j];
			j++;
		}
		else
		{
			str[i] = command[i + j];
			i++;
		}
	}
	str[i] = 0;
}

void	add_first_token(t_structok **token_list, t_structok *new)
{
	(*token_list) = new;
	(*token_list)->prev = *token_list;
	(*token_list)->next = *token_list;
}
