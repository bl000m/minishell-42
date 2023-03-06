/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/06 12:16:17 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	creating_cmd_list(t_minish *data)
{
	int		i;
	t_cmd	*node;

	i = 0;
	node = data->cmds;
	while (i < data->n_tokens)
		checking_token(data, &node, &i);
}

void	checking_token(t_minish *data, t_cmd **node, int *i)
{
	if (data->tokens[*i][0] == '<' && !data->tokens[*i][1])
		input_redirection(data, node, i);
	else if (data->tokens[*i][0] == '>')
		output_redirection(data, node, i);
	else if (!ft_strncmp(data->tokens[*i], "<<", 2))
		heredoc_handling(data, node, i);
	else if (data->tokens[*i][0] == '|')
		pipe_new_node(data, node, i);
	else
	{
		if (*i > 0 && (data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '>'))
			*i += 1;
		else
			stocking_cmd_and_arguments(data, node, i);
	}
}

void	stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i)
{
	int		arg;

	arg = 0;
	(*node)->full_cmd = malloc(sizeof(char *) * (count_token_cmd(data, i) + 1));
	if (!(*node)->full_cmd)
		return ;
	while (data->tokens[*i] && data->tokens[*i][0] != '|'
		&& data->tokens[*i][0] != '<' && data->tokens[*i][0] != '>')
	{
		(*node)->full_cmd[arg] = ft_strdup(data->tokens[*i]);
		adding_full_path(data, node);
		*i += 1;
		arg++;
	}
	(*node)->full_cmd[arg] = NULL;
}

void	adding_full_path(t_minish *data, t_cmd **node)
{
	if (is_builtin((*node)->full_cmd[0]))
		(*node)->full_path = NULL;
	else if (!is_builtin((*node)->full_cmd[0]))
	{
		(*node)->full_path = find_dir_command(data, (*node)->full_cmd[0]);
		// if (!(*node)->full_path == 0)
		// 	error_manager(3, data, node);
	}
}
