/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/03 13:19:01 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	home = find_varvalue(data, "HOME", 4);
	if (!home)
		home = ft_calloc(sizeof(char), 2);
	if (i - j > 0)
	{
		line = ft_substr(data->tokens[index], j, i - j);
		ft_lstadd_back(&data->aux, ft_lstnew(line));
	}
	ft_lstadd_back(&data->aux, ft_lstnew(mini_strdup(data, home)));
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

static void	expand_token(t_minish *data, int *index, int i, int j)
{
	int		dollar_sign;
	char	*subline;

	subline = NULL;
	dollar_sign = 0;
	if (j < i)
	{
		subline = ft_substr(data->tokens[*index], j, i - j);
		if (!subline)
			hard_exit(data, NULL, NULL);
		ft_lstadd_back(&data->aux, ft_lstnew(subline));
	}
	dollar_sign = check_if_dollar(data->tokens[*index]);
	free(data->tokens[*index]);
	if (dollar_sign)
		split_expandedtoken(data, index);
	else
		data->tokens[*index] = make_line_fromlst(data, &data->aux);
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

	index = -1;
	while (data->tokens && data->tokens[++index])
	{
		if (!data->tokens[index][0])
			continue ;
		j = 0;
		i = verify_expansion(data, index, &j);
		expand_token(data, &index, i, j);
	}
	regroup_tokens(data);
}
