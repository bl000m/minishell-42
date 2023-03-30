/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:53:40 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/30 12:19:24 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	count_token_cmd(t_minish *data, int *i)
{
	int	count;
	int temp;

	temp = *i;
	count = 0;

	while (data->tokens[temp] && data->tokens[temp][0] != '|'
		&& data->tokens[temp][0] != '\0' && data->tokens[temp][0] != '<'
		&& data->tokens[temp][0] != '>')
	{
		count++;
		temp++;
	}
	return (count);
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

int	heredoc_handling(t_minish *data, t_cmd **node, int *i)
{
	int		fd[2];

	if (!data->tokens[*i + 1])
		error_manager(11, data, NULL);
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
		error_manager(8, data, NULL);
	else
	{
		(*node)->file_in = open(data->tokens[*i + 1], O_RDONLY);
		if ((*node)->file_in == -1)
		{
			printf("%s: Permission denied\n", data->tokens[*i + 1]);
			*i += 1;
			return (1);
		}
			// error_manager(9, data, NULL);
		*i += 1;
	}
	return (0);
}

int	output_redirection(t_minish *data, t_cmd **node, int *i)
{
	if (!data->tokens[*i + 1])
		error_manager(8, data, NULL);
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
		error_manager(8, data, NULL);
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

