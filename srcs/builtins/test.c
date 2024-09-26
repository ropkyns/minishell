#include "../../include/minishell.h"

static int	name_already_exist(char *str, t_env *env)
{
	int		i;
	t_env	*temp;
	int		pos;

	temp = env;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!temp)
		return (-1);
	pos = 0;
	while (temp != NULL)
	{
		if (!ft_strncmp(temp->name, str, i)
			&& ((int)ft_strlen(temp->name) == i))
			return (pos);
		temp = temp->next;
		pos++;
	}
	return (-1);
}

t_env	*create_env_node(char *name)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = strdup(name);
	new_node->next = NULL;
	return (new_node);
}

int	main(void)
{
	t_env *env_list = create_env_node("USER");
	env_list->next = create_env_node("PATH");
	env_list->next->next = create_env_node("SHELL");
	env_list->next->next->next = create_env_node("HOME");

	char *test1 = "PATH=";
	char *test2 = "SHELL=";
	char *test3 = "EDITOR=";

	printf("Test avec '%s' -> position: %d\n", test1, name_already_exist(test1,
			env_list));
	printf("Test avec '%s' -> position: %d\n", test2, name_already_exist(test2,
			env_list));
	printf("Test avec '%s' -> position: %d\n", test3, name_already_exist(test3,
			env_list));
	t_env *temp;
	while (env_list != NULL)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->name);
		free(temp);
	}

	return (0);
}