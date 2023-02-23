/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/02/23 12:30:07 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief
 * Iterates over the list to create a line with the content of all the nodes
 *  and returns the line after free the list.
*/
static char	*create_expanded_line(t_list **lst)
{
	char	*line;
	t_list	*tmp;
	size_t	i;
	size_t	size;

	tmp = *lst;
	size = 0;
	while (*lst)
	{
		size += ft_strlen((*lst)->content);
		(*lst) = (*lst)->next;
	}
	line = ft_calloc(size + 1, sizeof(char));
	if (!line)
		return (NULL);
	size = 0;
	while (tmp)
	{
		i = ft_strlen(tmp->content);
		ft_memcpy(&line[size], tmp->content, i);
		size += i;
		tmp = tmp->next;
	}
	ft_lstclear(lst, free);
	return (line);
}

/**
 * @brief
 * Replaces the contenu of the $VAR with the value of it.
 * It will look after the '$' and continue while it's alphanumeric
 * then it will search the correspondent variable.
*/
static int	expand_var(t_minish *data, int index, int i, int j)
{
	int		k;
	char	*line;
	char	*tmp;

	if (i - j > 0)
	{
		line = ft_substr(data->tokens[index], j, i - j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	k = 1;
	while (ft_isalnum(data->tokens[index][i + k]))
		k++;
	tmp = find_varvalue(data, data->tokens[index] + i + 1, k - 1);
	line = ft_strdup(tmp);
	if (line)
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	return (i + k);
}

/**
 * @brief
 * Replaces the '~' with the value of $HOME.
*/
static int	expand_tilde(t_minish *data, int index, int i, int j)
{
	char	*line;
	char	*home;

	home = ft_strdup(find_varvalue(data, "HOME", 4));
	if (i == 0 && ft_strlen(data->tokens[index]) == 1)
	{
		free(data->tokens[index]);
		data->tokens[index] = home;
		return (1);
	}
	if (i - j > 0)
	{
		line = ft_substr(data->tokens[index], j, i - j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	line = home;
	if (line)
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	return (++i);
}

/**
 * @brief
 * Verifies if it have to expand the variables based on the quotes.
*/
static	int	verify_expansion(t_minish *data, int index, int *j)
{
	int		i;
	int		quote;
	char	*str;

	i = -1;
	quote = 0;
	str = data->tokens[index];
	while (str[++i])
	{
		if (are_quotes(str[i]) != quote && !quote)
			quote = are_quotes(str[i++]);
		if (str[i] == '$' && quote != 2)
			*j = expand_var(data, index, i, *j);
		if (str[i] == '~' && !quote && (i == 0 || str[i - 1] == ' ')
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '/'))
			*j = expand_tilde(data, index, i, *j);
		if (*j > i)
			i = *j - 1;
		if (quote == are_quotes(str[i]))
			quote = 0;
	}
	return (i);
}

/**
 * @brief
 * It will iterate over the input splited previously by another
 * function and putted in the data->tokens.
 *
 * If it's the case it will expand the variables into their values
 * For example if it's a ~ alone it will replace for the HOME path
 * and if it's a $VARIABLE or a "$VARIABLE" it will be replaced by the
 * variable's value.
 * And all things between two ' (simple quotes) are not modified.
 *
 * It has no return because the function will replace the values of
 * the pointers.
*/
void	expand_path(t_minish *data)
{
	int		index;
	int		i;
	int		j;
	char	*subline;

	index = -1;
	subline = NULL;
	while (data->tokens[++index])
	{
		j = 0;
		i = verify_expansion(data, index, &j);
		if (!data->aux)
			continue ;
		if (j < i)
		{
			subline = ft_substr(data->tokens[index], j, i - j);
			if (!subline)
				return ;
			ft_lstadd_back(&data->aux, ft_lstnew(subline));
		}
		free(data->tokens[index]);
		data->tokens[index] = create_expanded_line(&data->aux);
	}
}
