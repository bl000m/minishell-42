/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:54:59 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/27 17:00:59 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	creating_cmd_list(t_minish *data)
{
	int		i;
	int		res;
	t_cmd	*node;

	i = 0;
	res = 0;
	node = data->cmds;
	while (i < data->n_tokens && !res)
		res = checking_token(data, &node, &i);
	return (res);
}

int	checking_token(t_minish *data, t_cmd **node, int *i)
{
	int	res;

	res = 0;
	if (data->tokens[*i][0] == '<' && !data->tokens[*i][1])
		res = input_redirection(data, node, i);
	else if (data->tokens[*i][0] == '>'&& !data->tokens[*i][1])
		res = output_redirection(data, node, i);
	else if (!ft_strncmp(data->tokens[*i], "<<", 2))
		res = heredoc_handling(data, node, i);
	else if (!ft_strncmp(data->tokens[*i], ">>", 2))
		res = output_append_redirection(data, node, i);
	else if (!ft_strncmp(data->tokens[*i], ".", 1) && !data->tokens[*i + 1])
	{
		*i += 1;
		printf("bash: .: filename argument required\n");
		res = 1;
	}
	else if (!ft_strncmp(data->tokens[*i], "||", 2))
	{
		*i += 1;
		printf("syntax error near unexpected token\n");
		res = 1;
	}
	else if (data->tokens[*i][0] == '|')
		res = pipe_new_node(data, node, i);
	else
	{
		if (*i > 0 && (data->tokens[*i - 1][0] == '<'
			|| data->tokens[*i - 1][0] == '>'))
			*i += 1;
		else
			stocking_cmd_and_arguments(data, node, i);
	}
	return(res);
}

int	checking_quotes(char *token)
{
	return(token[0] == '\"' || token[0] == '\'');
}

char	*getting_rid_of_quotes(char *token)
{
	int		i;
	int		j;
	char	*result;

	i = 1;
	j = 0;
	result = malloc(sizeof(char) * (int)ft_strlen(token));
	if (!result)
		return (NULL);
	while(token[i] && token[i] != '\"' && token[i] != '\'')
		result[j++] = token[i++];
	result[i] = 0;
	// printf("result = %s\n", result);
	return (result);
}

int	stocking_cmd_and_arguments(t_minish *data, t_cmd **node, int *i)
{
	int		arg;
	int		res;
	char	*token_no_quotes;

	res = 0;
	arg = 0;
	(*node)->full_cmd = malloc(sizeof(char *) * (count_token_cmd(data, i) + 1));
	if (!(*node)->full_cmd)
		return (1);
	while (data->tokens[*i] && data->tokens[*i][0] != '|'
		&& data->tokens[*i][0] != '<' && data->tokens[*i][0] != '>')
	{
    if (checking_quotes(data->tokens[*i]))
		{
			token_no_quotes = getting_rid_of_quotes(data->tokens[*i]);
			(*node)->full_cmd[arg] = ft_strdup(token_no_quotes);
			free(token_no_quotes);
			token_no_quotes = NULL;
		}
		else
			(*node)->full_cmd[arg] = ft_strdup(data->tokens[*i]);
		res = adding_full_path(data, node);
		*i += 1;
		arg++;
	}
	(*node)->full_cmd[arg] = NULL;
	return (res);
}

int	adding_full_path(t_minish *data, t_cmd **node)
{
	if (is_builtin((*node)->full_cmd[0]))
		(*node)->full_path = NULL;
	else if (!is_builtin((*node)->full_cmd[0]))
	{
		if (find_varvalue(data, "PATH", 4))
			(*node)->full_path = find_dir_command(data, (*node)->full_cmd[0]);
		else
		{
			printf("No path is set. Not possibe to execute not built in functions\n");
			return (1);
		}
	}
	return (0);
}
