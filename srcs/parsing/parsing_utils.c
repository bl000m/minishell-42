/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:53:40 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 15:44:05 by mpagani          ###   ########.fr       */
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
			printf("Error creating pipe\n");
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
			printf("%s: Permission denied\n", data->tokens[*i + 1]);
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
			printf("%s: Permission denied\n", data->tokens[*i + 1]);
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
			printf("%s: Permission denied\n", data->tokens[*i + 1]);
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
		printf("syntax error near unexpected token\n");
		return (1);
	}
	else
	{
		create_new_cmd_list_node(node);
		*i += 1;
		return (0);
	}
}

