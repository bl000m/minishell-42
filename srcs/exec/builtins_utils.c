/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:17:56 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/04/01 15:10:34 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_dict(t_dict *node1, t_dict *node2)
{
	int		has_value;
	int		key_len;
	char	*key;
	char	*value;

	has_value = node1->has_value;
	key_len = node1->key_len;
	key = node1->key;
	value = node1->value;
	node1->has_value = node2->has_value;
	node1->key_len = node2->key_len;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->has_value = has_value;
	node2->key_len = key_len;
	node2->key = key;
	node2->value = value;
}

static void	dict_sort(t_dict **tosort)
{
	t_dict	*node;
	size_t	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		node = *tosort;
		while (node->next)
		{
			if (ft_memcmp(node->key, node->next->key, node->key_len) > 0)
			{
				swap_dict(node, node->next);
				swapped++;
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
	dict_sort(&sorted);
	if (sorted && !ft_memcmp(sorted->key, "_", sorted->key_len))
		sorted = sorted->next;
	while (sorted)
	{
		printf("declare -x %s", sorted->key);
		if (sorted->has_value)
			printf("=\"%s\"", sorted->value);
		printf("\n");
		sorted = sorted->next;
		if (sorted && !ft_memcmp(sorted->key, "_", sorted->key_len))
			sorted = sorted->next;
	}
	dict_free(&sorted);
}

char	*getpwd_forline(t_minish *data)
{
	char	*linepwd;

	// printf("passei na linha \n");
	// linepwd = getcwd(NULL, 0);
	// printf("linha %s\n", linepwd);
	// if (linepwd)
	// 	return (linepwd);
	linepwd = find_varvalue(data, "PWD", 3);
	if (linepwd)
		return (ft_strdup(linepwd));
	linepwd = ft_strdup("/.");
	return (linepwd);
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
	t_list	*prefix;
	char	*line1;
	char	*linepwd;
	size_t	len;

	linepwd = getpwd_forline(data);
	prefix = NULL;
	line1 = find_varvalue(data, "USER", 4);
	if (!line1)
		ft_lstadd_back(&prefix, ft_lstnew(ft_strdup("guest@minisHELL:")));
	else
		ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(line1, "@minisHELL:")));
	ft_lstadd_back(&prefix, ft_lstnew(linepwd));
	line1 = find_varvalue(data, "HOME", 4);
	if (line1)
		len = ft_strlen(line1);
	if (line1 && !ft_memcmp(ft_lstlast(prefix)->content, line1, len))
	{
		line1 = ft_strjoin("~", (char *)ft_lstlast(prefix)->content + len);
		free(ft_lstlast(prefix)->content);
		ft_lstlast(prefix)->content = line1;
	}
	ft_lstadd_back(&prefix, ft_lstnew(ft_strdup("$ ")));
	return (make_line_fromlst(&prefix));
}

/**
 * @brief
 * Gets the actuel path to create a string to put on the prefix of the executable
 * It will create the pattern
 * "LOGIN@@minishell:PATH$ "
 * (if that's the case will replace the HOME path by '~')
 * to be used in the readline()
 *
 * OBS : Is the same function as above, but in colors
*/
char	*get_color_lineprefix(t_minish *data)
{
	t_list	*prefix;
	char	*line1;
	size_t	len;

	prefix = NULL;
	line1 = find_varvalue(data, "USER", 4);
	if (!line1)
		ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(YELLOW, "guest")));
	else
		ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(BLUE, line1)));
	ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(RED, "@minisHELL:")));
	ft_lstadd_back(&prefix, ft_lstnew(ft_strdup(WHITE)));
	ft_lstadd_back(&prefix, ft_lstnew(getcwd(NULL, 0)));
	line1 = find_varvalue(data, "HOME", 4);
	if (line1)
		len = ft_strlen(line1);
	if (line1 && !ft_memcmp(ft_lstlast(prefix)->content, line1, len))
	{
		line1 = ft_strjoin("~", (char *)ft_lstlast(prefix)->content + len);
		free(ft_lstlast(prefix)->content);
		ft_lstlast(prefix)->content = line1;
	}
	ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(GREEN, "$ ")));
	ft_lstadd_back(&prefix, ft_lstnew(ft_strdup(NO_COLOR)));
	return (make_line_fromlst(&prefix));
}
