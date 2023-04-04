/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/03 11:51:41 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Iterates over the list to create a line with the content of all the nodes
 *  and returns the line after free the list.
*/
char	*make_line_fromlst(t_minish *data, t_list **lst)
{
	char	*line;
	t_list	*tmp;
	size_t	i;
	size_t	size;

	tmp = *lst;
	size = 0;
	while (tmp)
	{
		size += ft_strlen(tmp->content);
		tmp = tmp->next;
	}
	tmp = *lst;
	line = ft_calloc(size + 1, sizeof(char));
	if (!line)
		hard_exit(data, NULL, NULL);
	size = 0;
	while (tmp)
	{
		i = ft_strlen(tmp->content);
		ft_memcpy(&line[size], tmp->content, i);
		size += i;
		tmp = tmp->next;
	}
	return (ft_lstclear(lst, free), line);
}

/**
 * @brief
 * Iterates over the data->tokens
 * to free the empty pointers and regroup the not empty ones.
 * It will also update the data->n_tokens.
 * @param t_minish* data
 *
*/
void	regroup_tokens(t_minish *data)
{
	int		i;
	int		j;
	char	*swap;

	i = -1;
	while (++i < data->n_tokens)
	{
		if (!ft_strlen(data->tokens[i]))
		{
			j = 1;
			while (i + j < data->n_tokens && !ft_strlen(data->tokens[i + j]))
				j++;
			swap = data->tokens[i];
			data->tokens[i] = data->tokens[i + j];
			data->tokens[i + j] = swap;
		}
	}
	i = data->n_tokens - 1;
	while (!data->tokens[i] || !ft_strlen(data->tokens[i]))
	{
		free(data->tokens[i]);
		data->tokens[i] = NULL;
		i--;
	}
	data->n_tokens = i + 1;
}

int	check_if_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	realloc_data_tokens(t_minish *data, char **newtokens, int index)
{
	int		i;
	int		j;
	char	**ptr;

	i = -1;
	j = 0;
	ptr = data->tokens;
	data->tokens = ft_calloc(sizeof(char *), data->n_tokens + 1);
	if (!data->tokens)
	{
		data->tokens = ptr;
		hard_exit(data, newtokens, NULL);
	}
	while (++i < index)
		data->tokens[i] = ptr[i];
	while (newtokens[j])
		data->tokens[i++] = newtokens[j++];
	while (i < data->n_tokens)
		data->tokens[i++] = ptr[++index];
	free(newtokens);
	free(ptr);
}

void	split_expandedtoken(t_minish *data, int *index)
{
	char	*line1;
	char	*line2;
	int		i;
	char	**tokens;

	i = 0;
	line1 = make_line_fromlst(data, &data->aux);
	line2 = getting_rid_of_quotes(data, line1);
	free(line1);
	tokens = ft_split(line2, ' ');
	free(line2);
	while (tokens[i])
		i++;
	if (i == 1)
	{
		data->tokens[*index] = tokens[0];
		free(tokens);
	}
	else
	{
		data->n_tokens += i - 1;
		realloc_data_tokens(data, tokens, *index);
		*index += i - 1;
	}
}
