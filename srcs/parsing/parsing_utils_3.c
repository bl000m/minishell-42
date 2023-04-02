/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:20:49 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 15:42:32 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(t_minish *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i][0] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	create_new_cmd_list_node(t_cmd **node)
{
	t_cmd	*new_elem;
	t_cmd	*ptr;

	if (!(*node) || !(node))
		return ;
	ptr = *node;
	while (ptr->next)
		ptr = ptr->next;
	new_elem = ft_calloc(sizeof(t_cmd), 1);
	if (!new_elem)
		return ;
	new_elem->input = STDIN_FILENO;
	new_elem->output = STDOUT_FILENO;
	ptr->next = new_elem;
	*node = (*node)->next;
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "unset", 5) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "pwd", 3) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

int	odd_quotes(char *s)
{
	int	i;
	int	count_simple;
	int	count_double;

	i = 0;
	count_simple = 0;
	count_double = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			count_simple++;
		if (s[i] == '\"')
			count_double++;
		i++;
	}
	if (count_simple % 2 != 0 || count_double % 2 != 0)
		return (1);
	else
		return (0);
}
