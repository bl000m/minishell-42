/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/24 18:04:23 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>


// void	create_new_cmd_list_node(t_minish *data, char *content)
// {
// 	t_list	*new_elem;

// 	new_elem = malloc(sizeof(*new_elem));
// 	if (!new_elem)
// 		return ;
// 	new_elem->content = ft_strdup(content);
// 	new_elem->next = NULL;
// 	data->cmds->next = new_elem;
// 	data->cmds = data->cmds->next;
// }

int	count_token_cmd(t_minish *data, int *i)
{
	int	count;

	count = *i;
	while (data->tokens[count] && data->tokens[count][0] != '|' && data->tokens[count][0] != '\0'
	&& data->tokens[count][0] != '<' && data->tokens[count][0] != '>')
		count++;
	return (count);
}

void	stocking_cmd_and_arguments(t_minish *data, int *i)
{
	char	**full_cmd;
	int	j = 0;

	full_cmd = malloc(sizeof(char *) * count_token_cmd(data, i) + 1);
	if (!full_cmd)
		return ;
	while (data->tokens[*i] && data->tokens[*i][0] != '|'
		&& data->tokens[*i][0] != '<' && data->tokens[*i][0] != '>')
	{
		full_cmd[*i] = ft_strdup(data->tokens[*i]);
		*i += 1;
	}
	full_cmd[*i] = NULL;
	data->cmds->full_cmd = full_cmd;
	while (data->cmds->full_cmd[j])
	{
		ft_printf("%s, ", data->cmds->full_cmd[j]);
		if (data->cmds->full_cmd[j + 1] == NULL)
			printf("\n");
		j++;
	}
	// if (i == 0)
	// 	data->cmds->content = ft_strdup(data->tokens[*i]);
	// else
	// 	create_new_cmd_list_node(data, data->tokens[*i]);
}


void	checking_token(t_minish *data, int *i)
{
	if (data->tokens[*i][0] == '<' && data->tokens[*i + 1])
	{
		data->cmds->file_in = open(data->tokens[*i + 1], O_RDONLY);
		if (data->cmds->file_in == -1)
				ft_printf("INPUT ERROR: %s\n", strerror(errno));
		ft_printf("in < scenario\n");
	}
	else if (data->tokens[*i][0] == '>' && data->tokens[*i + 1])
	{
		data->cmds->file_out = open(data->tokens[*i + 1], O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
		if (data->cmds->file_out == -1)
		error_manager(5, data);
	}
	else if (data->tokens[*i][0] == '|')
	{
		if (i == 0 || data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '>' || *i != data->n_tokens - 1)
			error_manager(7, data);
		else
			return ;
	}
	else
	{
		stocking_cmd_and_arguments(data, i);
	}
}

void	creating_cmd_list(t_minish *data)
{
	int		i;
	// int		j;
	// t_cmd	*head;

	// head = data->cmds;
	i = 0;
	// j = 0;
	while (i < data->n_tokens)
	{
		// ft_printf("i = %d\n", i);
		// ft_printf("n_token: %d\n", data->n_tokens);
		// ft_printf("first letter of first token= %c\n", data->tokens[i][0]);
		checking_token(data, &i);
		i++;
	}
	// while (head->next)
	// {
		// while (head->full_cmd[j])
		// {
		// 	ft_printf("%s, ", head->full_cmd[j]);
			// ft_printf("%s, ", head->full_cmd[j]);
			// if (head->full_cmd[j + 1] == NULL)
			// 	printf("\n");
		// 	j++;
		// }
		// head = head->next;
	// }
}
