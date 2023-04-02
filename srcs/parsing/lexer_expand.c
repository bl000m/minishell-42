/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/01 21:42:58 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * Iterates over the list to create a line with the content of all the nodes
 *  and returns the line after free the list.
*/
char	*make_line_fromlst(t_list **lst)
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
	k = 2;
	if (ft_isalpha(data->tokens[index][i + 1])
		|| data->tokens[index][i + 1] == '_')
		while (ft_isalnum(data->tokens[index][i + k])
			|| data->tokens[index][i + k] == '_')
			k++;
	if (data->tokens[index][i + 1] == '?')
		line = ft_itoa(g_status);
	else
	{
		tmp = find_varvalue(data, data->tokens[index] + i + 1, k - 1);
		line = ft_strdup(tmp);
	}
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
	if (!home)
		home = ft_calloc(sizeof(char), 2);
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
	// line = home;
	// if (line)
		ft_lstadd_back(&data->aux, ft_lstnew(home));
	printf("~=>#%s#\n", home);
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
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' '
			&& quote != 2 && (!index || (data->tokens[index - 1]
					&& ft_memcmp(data->tokens[index - 1], "<<", 3))))
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
		return ;
	while (++i < index)
		data->tokens[i] = ptr[i];
	while (newtokens[j])
		data->tokens[i++] = newtokens[j++];
	while (i < data->n_tokens)
		data->tokens[i++] = ptr[++index];
	free(newtokens);
	free(ptr);
	// data->tokens = NULL;
	// return ;
}

void	split_expandedtoken(t_minish *data, int *index)
{
	char	*line1;
	char	*line2;
	int		i;
	char	**tokens;

	i = 0;
	line1 = make_line_fromlst(&data->aux);
	line2 = getting_rid_of_quotes(line1);
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
		// printf("token %d => #%s#\n", i, tokens[i]);
	}
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
	int		dollar;

	index = -1;
	subline = NULL;
	while (data->tokens[++index])
	{
		// printf("str antes => |%s|\n", data->tokens[index]);
		dollar = 0;
		j = 0;
		i = verify_expansion(data, index, &j);
		if (j < i)
		{
			subline = ft_substr(data->tokens[index], j, i - j);
			if (!subline)
				return ;
			ft_lstadd_back(&data->aux, ft_lstnew(subline));
		}
		dollar = check_if_dollar(data->tokens[index]);
		free(data->tokens[index]);
		if (dollar)
			split_expandedtoken(data, &index);
			// data->tokens[index] = getting_rid_of_quotes(make_line_fromlst(&data->aux));
		else
			data->tokens[index] = make_line_fromlst(&data->aux);
		// printf("str depois => |%s|\n", data->tokens[index]);
	}
	regroup_tokens(data);
}

int	heredoc_expand_aux(t_minish *data, char *line, int i, int j)
{
	int		k;
	char	*tmp;

	if (i - j > 0)
		ft_lstadd_back(&data->aux, ft_lstnew(ft_substr(line, j, i - j)));
	k = 2;
	if (ft_isalpha(line[i + 1]) || line[i + 1] == '_')
		while (ft_isalnum(line[i + k]) || line[i + k] == '_')
			k++;
	if (line[i + 1] == '?')
		line = ft_itoa(g_status);
	else
	{
		tmp = find_varvalue(data, line + i + 1, k - 1);
		line = ft_strdup(tmp);
	}
	if (!line)
		line = ft_calloc(1, sizeof(char));
	ft_lstadd_back(&data->aux, ft_lstnew(line));
	return (i + k);
}

/**
 * @brief
 * Expands all the variables, whitout handling the quotes.
 * To be used by heredoc.
*/
char	*heredoc_expand(t_minish *data, char *line)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			j = heredoc_expand_aux(data, line, i, j);
			i = j - 1;
		}
	}
	if (data->aux)
	{
		ft_lstadd_back(&data->aux, ft_lstnew(ft_substr(line, j, i - j)));
		return (make_line_fromlst(&data->aux));
	}
	return (NULL);
}
