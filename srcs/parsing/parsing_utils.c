/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:53:40 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/25 17:03:26 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_new_cmd_list_node(t_cmd **node, t_minish *data)
{
	t_cmd	*new_elem;
	t_cmd	*ptr;

	ptr = *node;
	while (ptr->next)
		ptr = ptr->next;
	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
		return ;
	new_elem->full_cmd = NULL;
	new_elem->full_path = NULL;
	new_elem->input = data->pipe[0];
	new_elem->output = 1;
	new_elem->next = NULL;
	ptr->next = new_elem;
	*node = (*node)->next;
}

int	count_token_cmd(t_minish *data, int *i)
{
	int	count;

	count = *i;
	while (data->tokens[count] && data->tokens[count][0] != '|' && data->tokens[count][0] != '\0'
	&& data->tokens[count][0] != '<' && data->tokens[count][0] != '>')
		count++;
	return (count);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd,"unset", 5) || !ft_strncmp(cmd,"env", 3) || !ft_strncmp(cmd,"pwd", 3)
		|| !ft_strncmp(cmd,"export", 6) || !ft_strncmp(cmd,"cd", 2) || !ft_strncmp(cmd,"echo", 4)
		|| !ft_strncmp(cmd,"exit", 4))
		return (1);
	return (0);
}

void	input_redirection(t_minish *data, int *i)
{
	if (!data->tokens[*i + 1])
		error_manager(8, data);
	else
	{
		data->cmds->input = open(data->tokens[*i + 1], O_RDONLY);
		if (data->cmds->input == -1)
				ft_printf("INPUT ERROR: %s\n", strerror(errno));
	}
}

void	output_redirection(t_minish *data, int *i)
{
	if (!data->tokens[*i + 1])
		error_manager(8, data);
	else
	{
		data->cmds->output = open(data->tokens[*i + 1], O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
		if (data->cmds->output == -1)
			error_manager(5, data);
	}
}

void	pipe_new_node(t_minish *data, t_cmd **node, int *i)
{
	if (i == 0 || data->tokens[*i - 1][0] == '<'
		|| data->tokens[*i - 1][0] == '>' || *i == data->n_tokens - 1)
		error_manager(7, data);
	else
	{
		(*node)->output = data->pipe[1];
		create_new_cmd_list_node(node, data);
		*i += 1;
	}
}

int	cmds_number(t_minish *data)
{
	int		count;
	t_cmd	*ptr;

	count = 0;
	ptr = data->cmds;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}
