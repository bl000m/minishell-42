/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/30 11:29:19 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	check_quotes_in_token(t_minish *data)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (data->tokens[++i])
	{
		tmp = getting_rid_of_quotes(data->tokens[i]);
		free(data->tokens[i]);
		data->tokens[i] = tmp;
	}
}

void	create_within_quotes(t_minish *data)
{
	int	*quotes;
	int	i;

	quotes = ft_calloc(data->n_tokens, sizeof(int));
	if (!quotes)
		return ;
	i = -1;
	while (data->tokens[++i])
	{
		if (data->tokens[i][0] == '\'' || data->tokens[i][0] == '\"')
			quotes[i] = 1;
	}
	data->within_quotes = quotes;
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
		// printf("str antes => |%s|\n", data->tokens[index]);
		j = 0;
		i = verify_expansion(data, index, &j);
		if (j < i)
		{
			subline = ft_substr(data->tokens[index], j, i - j);
			if (!subline)
				return ;
			ft_lstadd_back(&data->aux, ft_lstnew(subline));
		}
		free(data->tokens[index]);
		data->tokens[index] = make_line_fromlst(&data->aux);
		printf("str depois => |%s|\n", data->tokens[index]);
	}
	regroup_tokens(data);
	// create_within_quotes(data);
	// printf("pas moi\n");
	// check_quotes_in_token(data);
	// index = -1;
	// while (data->tokens[++index])
	// 	printf("token final => |%s|\n", data->tokens[index]);
}







// static int	is_delimiter(char *str, int i)
// {
// 	i--;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\'' || str[i] == '\"'))
// 		i--;
// 	if (str[i] && str[i - 1] && str[i] == '<' && str[i - 1] == '<')
// 		return (1);
// 	return (0);
// }


/**
 * @brief
 * Replaces the contenu of the $VAR with the value of it.
 * It will look after the '$' and continue while it's alphanumeric
 * then it will search the correspondent variable.
*/
static int	expand_var_line(t_minish *data, int i, int *j)
{
	int		k;
	char	*line;
	char	*tmp;

	if (i - *j > 0)
	{
		line = ft_substr(data->input, *j, i - *j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	k = 2;
	if (ft_isalpha(data->input[i + 1])
		|| data->input[i + 1] == '_')
		while (ft_isalnum(data->input[i + k])
			|| data->input[i + k] == '_')
			k++;
	if (data->input[i + 1] == '?')
		line = ft_itoa(g_status);
	else
	{
		tmp = find_varvalue(data, data->input + i + 1, k - 1);
		line = ft_strdup(tmp);
	}
	if (line)
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	*j = i + k;
	return (i + k - 1);
}

/**
 * @brief
 * Replaces the '~' with the value of $HOME.
*/
static int	expand_tilde_line(t_minish *data, int i, int *j)
{
	char	*line;
	char	*home;

	home = ft_strdup(find_varvalue(data, "HOME", 4));
	if (!home)
		home = ft_calloc(sizeof(char), 2);
	// if (i == 0 && ft_strlen(data->tokens[index]) == 1)
	// {
	// 	free(data->tokens[index]);
	// 	data->tokens[index] = home;
	// 	return (1);
	// }
	if (i - *j > 0)
	{
		line = ft_substr(data->input, *j, i - *j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	// line = home;
	// if (line)
		ft_lstadd_back(&data->aux, ft_lstnew(home));
	printf("~=>#%s#\n", home);
	*j = i + 1;
	return (i);
}

static int	expand_open_heredoc(t_minish *data, int i, int *j)
{
	char	*line;

	if (i - *j > 0)
	{
		line = ft_substr(data->input, *j, i - *j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	*j = i;
	while (data->input[i] && data->input[i] == '<')
		i++;
	line = ft_substr(data->input, *j, i - *j);
	ft_lstadd_back(&data->aux, ft_lstnew(line));
	*j = i + 1;
	return (i);
}

void	expand_path_line(t_minish *data)
{
	int		i;
	int		j;
	int		quote;
	char	*str;

	str = data->input;
	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (are_quotes(str[i]) != quote && !quote)
			quote = are_quotes(str[i++]);
		if (str[i] == '<' && !quote)
			i = expand_open_heredoc(data, i, &j);
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' '
			&& quote != 2 && (!data->aux || ft_memcmp(ft_lstlast(data->aux)->content, "<<", 3)))
			i = expand_var_line(data, i, &j);
		if (str[i] == '~' && !quote && (i == 0 || str[i - 1] == ' ')
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '/'))
			i = expand_tilde_line(data, i, &j);
		// if (*j > i)
		// 	i = *j - 1;
		if (quote == are_quotes(str[i]))
			quote = 0;
	}
	if (j < i)
		{
			str = ft_substr(data->input, j, i - j);
			if (!str)
				return ;
			ft_lstadd_back(&data->aux, ft_lstnew(str));
		}
		free(data->input);
		data->input = make_line_fromlst(&data->aux);
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
