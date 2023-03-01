/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:17:56 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/03/01 12:49:50 by fbelfort         ###   ########.fr       */
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

void	print_sorted(t_dict *envp, int fd)
{
	t_dict	*sorted;

	sorted = dict_duplst(envp);
	if (!sorted)
		return ;
	dict_sort(sorted);
	while (sorted)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(sorted->key, fd);
		if (sorted->has_value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(sorted->value, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
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

	line2 = NULL;
	line1 = getcwd(NULL, 0);
	line2 = find_varvalue(data, "HOME", 4);
	len = ft_strlen(line2);
	if (line2 && !ft_memcmp(line2, line1, len))
	{
		line2 = ft_strjoin("~", &line1[len]);
		free(line1);
		line1 = line2;
	}
	line2 = ft_strjoin(line1, "$ ");
	free(line1);
	line1 = ft_strjoin(find_varvalue(data, "USER", 4), "@minishell:");
	prefix = ft_strjoin(line1, line2);
	free(line2);
	free(line1);
	return (prefix);
}
