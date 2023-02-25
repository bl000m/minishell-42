/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/25 16:51:45 by mpagani          ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd,"unset", 5) || !ft_strncmp(cmd,"env", 3) || !ft_strncmp(cmd,"pwd", 3)
		|| !ft_strncmp(cmd,"export", 6) || !ft_strncmp(cmd,"cd", 2) || !ft_strncmp(cmd,"echo", 4)
		|| !ft_strncmp(cmd,"exit", 4))
		return (1);
	return (0);
}

void	stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i)
{
	int	j;

	j = 0;
	(*node)->full_cmd = malloc(sizeof(char *) * count_token_cmd(data, i) + 1);
	if (!(*node)->full_cmd)
		return ;
	while (data->tokens[*i] && data->tokens[*i][0] != '|'
		&& data->tokens[*i][0] != '<' && data->tokens[*i][0] != '>')
	{
		(*node)->full_cmd[j] = ft_strdup(data->tokens[*i]);
		if (is_builtin((*node)->full_cmd[0]))
			(*node)->full_path = NULL;
		else if(!is_builtin((*node)->full_cmd[0]))
			(*node)->full_path = find_dir_command(data, (*node)->full_cmd[0]);
		*i += 1;
		j++;
	}
	(*node)->full_cmd[*i] = NULL;
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
	if (data->tokens[*i][0] == '<')
		input_redirection(data, i);
	else if (data->tokens[*i][0] == '>')
		output_redirection(data, i);
	else if (data->tokens[*i][0] == '|')
	{
		if (i == 0 || data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '>' || *i == data->n_tokens - 1)
			error_manager(7, data);
		else
		{
			create_new_cmd_list_node(node);
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
		checking_token(data, &node, &i);
}
