/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:53:40 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/02 16:06:29 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_handling(t_minish *data, t_cmd **node, int *i)
{
	int		fd[2];

	if (!data->tokens[*i + 1])
	{
		printf("Error manager to be set\n");
		return (1);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			error_manager(0, EC_PIPE, NULL, EXIT_FAILURE);
			*i += 1;
			return (1);
		}
		(*node)->input = fd[0];
		here_doc(data, i, fd[1]);
		*i += 1;
		if (g_status)
			return (1);
	}
	return (0);
}

int	input_redirection(t_minish *data, t_cmd **node, int *i)
{
	if (!data->tokens[*i + 1])
	{
		printf("Error manager to be set\n");
		return (1);
	}
	else
	{
		(*node)->file_in = open(data->tokens[*i + 1], O_RDONLY);
		if ((*node)->file_in == -1)
		{
			printf("%s: %s\n", data->tokens[*i + 1], strerror(errno));
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

int	output_redirection(t_minish *data, t_cmd **node, int *i)
{
	if (!data->tokens[*i + 1])
	{
		printf("Error manager to be set\n");
		return (1);
	}
	else
	{
		(*node)->file_out = open(data->tokens[*i + 1], O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		if ((*node)->file_out == -1)
		{
			printf("%s: %s\n", data->tokens[*i + 1], strerror(errno));
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

int	output_append_redirection(t_minish *data, t_cmd **node, int *i)
{
	if (!data->tokens[*i + 1])
	{
		printf("Error manager to be set\n");
		return (1);
	}
	else
	{
		(*node)->file_out = open(data->tokens[*i + 1], O_CREAT
				| O_WRONLY | O_APPEND, 0644);
		if ((*node)->file_out == -1)
		{
			error_manager(0, EC_PERMISSION, NULL, EXIT_FAILURE);
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

int	pipe_new_node(t_minish *data, t_cmd **node, int *i)
{
	if (*i == 0 || (*i > 0 && (data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '|'
		|| data->tokens[*i - 1][0] == '>' || *i == data->n_tokens - 1)))
	{
		*i += 1;
		error_manager(0, EC_SINTAX2, NULL, EXIT_FAILURE);
		return (1);
	}
	else
	{
		create_new_cmd_list_node(data, node);
		*i += 1;
		return (0);
	}
}
