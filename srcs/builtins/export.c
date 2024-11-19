/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjameau <mjameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:51:39 by mjameau           #+#    #+#             */
/*   Updated: 2024/11/12 11:31:52 by mjameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* Si la fonction export n'a pas d'arguments
alors on affiche tout env avec declare -x devant
*/
static bool	export_no_args(t_env *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = make_env_tab(env);
	if (!arr)
		return (false);
	sort_array(arr, len_env(env));
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(arr);
	return (true);
}



// static bool export_no_args(t_env *env)
// {
//     char **arr;
//     int i;
//     int j;

//     arr = make_env_tab(env);
//     if (!arr)
//     {
//         printf("Failed to create environment array\n");
//         return false;
//     }

//     printf("Array created by make_env_tab:\n");
//     for (i = 0; arr[i]; i++)
//     {
//         printf("%s\n", arr[i]);
//     }

//     sort_array(arr, len_env(env));

//     i = 0;
//     while (arr[i])
//     {
//         printf("declare -x ");
//         j = 0;
//         while (arr[i][j] && arr[i][j] != '=')
//             printf("%c", arr[i][j++]);
//         if (arr[i][j] && arr[i][j] == '=')
//             printf("=\"%s\"\n", &arr[i][j + 1]);
//         else
//             printf("\n");
//         i++;
//     }
//     free(arr);

//     return true;
// }


/*
* On regarde si le nom de la variable commence bien par un alpha
ou un _, ensuite on regarde si la valeur de la variable n'a bien que
des alnum ou un _
*/
static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/*
 *  On verifie si str existe dans la liste chainee des env
 on parcourt la liste et on retourne l'index de la variable (j)
 si on la trouve
 */
static int	exist(char *str, t_env *env)
{
	int		i;
	int		j;
	t_env	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0'
				|| tmp->str[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

/*
* Fonction pour export la value,
	on verifie si la variable existe (et si oui a quel index)
et on va a cet index, on free sa value et on la met a jour.
 Si elle existe pas on ajoute une nouvelle node
*/
bool export_value(t_env **env, char *str)
{
    char *value;
    t_env *current = *env;
    t_env *prev = NULL;    
    char *equals_sign = strchr(str, '=');
    char *key;
    char *full_str;
    size_t key_len, value_len;

    if (equals_sign)
    {
        key = ft_strndup(str, equals_sign - str);
        value = ft_strdup(equals_sign + 1);
    }
    else
    {
        key = ft_strdup(str);
        value = ft_strdup("");
    }
    if (strstr(value, key) != NULL && value[0] == '$')
    {
        free(key);
        free(value);
        return false;
    }
    key_len = ft_strlen(key);
    value_len = ft_strlen(value);
    full_str = malloc(key_len + 1 + value_len + 1); 
    if (!full_str)
    {
        free(key);
        free(value);
        return false;
    }
    ft_memcpy(full_str, key, key_len);
    full_str[key_len] = '=';
    ft_memcpy(full_str + key_len + 1, value, value_len);
    full_str[key_len + 1 + value_len] = '\0';
    while (current)
    {
        if (ft_strcmp(current->name, key) == 0)
        {
            free(current->value);
            free(current->str);
            current->value = value;
            current->str = full_str;
            free(key);
            return true;
        }
        prev = current;
        current = current->next;
    }
    if (add_node_env(env, full_str))
    {
        free(key);
        return true;
    }
    else
    {
        free(key);
        free(full_str);
        return false;
    }
}




// bool export_value(t_env **env, const char *str)
// {
//     char *key;
//     char *value;
//     t_env *current = *env;
//     t_env *prev = NULL;

//     // Handle variables without values
//     char *equals_sign = strchr(str, '=');
//     if (equals_sign)
//     {
//         key = ft_strndup(str, equals_sign - str);
//         value = ft_strdup(equals_sign + 1);
//     }
//     else
//     {
//         key = strdup(str);
//         value = strdup("");
//     }

//     // Find the existing key in the environment list
//     while (current)
//     {
//         if (strcmp(current->name, key) == 0)
//         {
//             free(current->value);
//             current->value = value;
//             free(key);
//             printf("Updated environment value: %s\n", str); // Debug statement
//             return true;
//         }
//         prev = current;
//         current = current->next;
//     }

//     // Add the new key to the environment list
//     t_env *new_node = malloc(sizeof(t_env));
//     if (!new_node)
//     {
//         printf("Memory allocation failed for new environment node\n");
//         free(key);
//         free(value);
//         return false;
//     }

//     new_node->name = key;
//     new_node->value = value;
//     new_node->next = NULL;
//     if (prev)
//         prev->next = new_node;
//     else
//         *env = new_node;
//     printf("Added new value to environment: %s\n", str); // Debug statement

//     return true;
// }


/*
* Si pas d'arguments on affiche toutes les variables d'env, sinon on check
si la syntaxe est valide et ensuite on export!
*/
int	ft_export(t_env **env, char **str)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !export_no_args((*env)))
			return (1);
		return (0);
	}
	while (str[i])
	{
		if (!valid_identifier(str[i]))
		{
			printf("bash: export: '%s': invalid identifier\n", str[i]);
			exit_code = 1;
		}
		else if (!export_value(env, str[i]))
			return (1);
		i++;
	}
	free(str[i]);
	return (exit_code);
}
