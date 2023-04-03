/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:17:56 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/04/03 14:41:22 by mpagani          ###   ########.fr       */
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
	t_dict	*temp;

	sorted = dict_duplst(envp);
	if (!sorted)
		return ;
	dict_sort(&sorted);
	temp = sorted;
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
	dict_free(&temp);
}

void	export_aux(t_minish *data, char *arg)
{
	size_t	len;
	t_dict	*ptr;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (is_validvarname(arg, len) && ft_memcmp(arg, "_", len))
	{
		ptr = dict_findvar(data->envp, arg, len);
		if (!ptr)
			dict_addback(&data->envp, dict_newnode(arg));
		if (arg[len] == '=' && ptr)
			set_varvalue(data->envp, ptr->key, ptr->key_len, &arg[len + 1]);
	}
	else if (ft_memcmp(arg, "_", len))
		error_manager(0, EC_EXPORT, arg, EXIT_FAILURE);
}
