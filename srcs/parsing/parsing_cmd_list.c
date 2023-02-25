/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/25 15:12:56 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>


void	create_new_cmd_list_node(t_cmd **node)
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
	new_elem->input = 0;
	new_elem->output = 0;
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

void	stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i)
{
	// char	**full_cmd;
	(*node)->full_cmd = malloc(sizeof(char *) * count_token_cmd(data, i) + 1);
	if (!(*node)->full_cmd)
		return ;
	while (data->tokens[*i] && data->tokens[*i][0] != '|'
		&& data->tokens[*i][0] != '<' && data->tokens[*i][0] != '>')
	{
		(*node)->full_cmd[*i] = ft_strdup(data->tokens[*i]);
		printf("node= %s\n", (*node)->full_cmd[*i]);
		*i += 1;
	}
	(*node)->full_cmd[*i] = NULL;
	// data->cmds->full_cmd = full_cmd;
	// *i += 1;
	ft_printf("i in stocking = %d\n", *i);
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

void	checking_token(t_minish *data, t_cmd **node, int *i)
{
	printf("i in checking token = %d\n", *i);
	if (data->tokens[*i][0] == '<')
		input_redirection(data, i);
	else if (data->tokens[*i][0] == '>')
		output_redirection(data, i);
	else if (data->tokens[*i][0] == '|')
	{
		printf("yes it's |\n");
		if (i == 0 || data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '>' || *i == data->n_tokens - 1)
			error_manager(7, data);
		else
		{
			create_new_cmd_list_node(node);
			// printf("data->cmds->full_cmd = %s\n", data->cmds->full_cmd[0]);
			ft_printf("HERE?\n");

			*i += 1;
		}
	}
	else
		stocking_cmd_and_arguments(data, node, i);
}

void	creating_cmd_list(t_minish *data)
{
	int		i;
	t_cmd	*node;

	i = 0;
	node = data->cmds;
	printf("token 2 = %c\n", data->tokens[0][0]);
	while (i < data->n_tokens)
	{
		checking_token(data, &node, &i);
		// printf("node = %s\n", node->full_cmd[0]);
		ft_printf("i in creating = %d\n", i);
		// i++;
	}
	// printf("data->cmds->full_cmd = %s\n", data->cmds->full_cmd[0]);
	// printf("data->cmds->full_cmd = %s\n", data->cmds->next->full_cmd[0]);
	// printf("%s\n", node->full_cmd[0]);
	// printf("%s\n", head->next->full_cmd[0]);
	// printf("%s\n", data->cmds->full_cmd[1]);
	// printf("%s\n", data->cmds->full_cmd[2]);
}
