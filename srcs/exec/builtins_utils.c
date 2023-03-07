/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: FelipeBelfort <FelipeBelfort@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:17:56 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/03/07 18:47:23 by FelipeBelfo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	swap_dict(t_dict *node1, t_dict *node2)
{
	t_dict	*tmp;

	tmp = node1;
	tmp->next = node2->next;
	node2->next = tmp;
	node1 = node2;
}

static void	dict_sort(t_dict *tosort)
{
	t_dict	*node;
	size_t	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		node = tosort;
		while (node->next)
		{
			if (ft_memcmp(node->key, node->next->key, node->key_len) > 0)
			{
				swap_dict(node, node->next);
				swapped = 1;
			}
			node = node->next;
		}
	}
}

void	print_sorted(t_dict *envp)
{
	t_dict	*sorted;

	sorted = dict_duplst(envp);
	if (!sorted)
		return ;
	dict_sort(sorted);
	while (sorted)
	{
		printf("declare -x %s", sorted->key);
		if (sorted->has_value)
			printf("=\"%s\"", sorted->value);
		printf("\n");
		sorted = sorted->next;
	}
	dict_free(&sorted);
}

/**
 * @brief
 * Gets the actuel path to create a string to put on the prefix of the executable
 * It will create the pattern
 * "LOGIN@@minishell:PATH$ "
 * (if that's the case will replace the HOME path by '~')
 * to be used in the readline()
*/
char	*get_lineprefix(t_minish *data)
{
	char	*line1;
	char	*line2;
	char	*prefix;
	size_t	len;

	line1 = ft_strjoin(find_varvalue(data, "PWD", 3), "\e[1;34m$ \e[0m");
	line2 = find_varvalue(data, "HOME", 4);
	if (line2)
		len = ft_strlen(line2);
	if (line2 && !ft_memcmp(line2, line1, len))
	{
		line2 = ft_strjoin("~", &line1[len]);
		free(line1);
		line1 = line2;
	}
	prefix = find_varvalue(data, "USER", 4);
	if (!prefix)
		prefix = ft_strjoin("\e[1;33mguest", "\e[1;31m@minisHell:\e[1;30m");
	else
		prefix = ft_strjoin(prefix, "\e[1;31m@minisHell:\e[1;30m");
	line2 = ft_strjoin(prefix, line1);
	free(line1);
	free(prefix);
	return (line2);
}
