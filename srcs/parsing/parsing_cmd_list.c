/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/24 12:03:20 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>


void	create_new_cmd_list_node(t_minish *data)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(*new_elem));
	if (!new_elem)
		return ;
	new_elem->content = NULL;
	new_elem->next = NULL;
	data->cmds->next = new_elem;
	data->cmds = data->cmds->next;
}

void	checking_token(t_minish *data, int i)
{
	if (data->tokens[i][0] == '<' && data->tokens[i + 1])
	{
		data->file_in = open(data->tokens[i + 1], O_RDONLY);
		if (data->file_in == -1)
				ft_printf("INPUT ERROR: %s\n", strerror(errno));
	}
	else if (data->tokens[i][0] == '>' && data->tokens[i + 1])
	{
		data->file_out = open(data->tokens[i + 1], O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
		if (data->file_out == -1)
		error_manager(5, data);
	}
	else if (data->tokens[i][0] == '|' && data->tokens[i + 1][0])
	{
		if (i == 0 || data->tokens[i - 1][0] == '<' || data->tokens[i - 1][0] == '>')
			error_manager(7, data);
		else if (i == data->n_tokens - 1)
		{
			while (1)
			{
				data->completing_input = readline("> ");
				if (data->completing_input)
					break ;
			}
			if (data->completing_input)
				create_new_cmd_list_node(data);
			data->cmds->content = ft_strdup(data->completing_input);
		}
		else
			create_new_cmd_list_node(data);
	}
	else
		data->cmds->content = ft_strdup(data->tokens[i]);
}

void	creating_cmd_list(t_minish *data)
{
	int	i;

	i = 0;
	while (i < data->n_tokens)
	{
		checking_token(data, i);
		i++;
	}
}
