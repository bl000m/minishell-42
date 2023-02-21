/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/02/21 17:49:16 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_expanded_line(t_list **lst)
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

static int	expand_var(t_minish *data, t_list **lst, char *str, int i, int j)
{
	int		k;
	char	*line;

	if (i - j > 0)
	{
		line = ft_substr(str, j, i - j);
		ft_lstadd_back(lst, ft_lstnew(line));
	}
	k = 1;
	while (ft_isalnum(str[i + k]))
		k++;
	line = find_varvalue(data, str + i + 1, k);
	if (line)
		ft_lstadd_back(lst, ft_lstnew(line));
	return (i + k);
}

static int	expand_tilde(t_minish *data, t_list **lst, char *str, int i, int j)
{
	char	*line;

	if (i == 0 && ft_strlen(str) == 1)
	{
		free(str);
		str = find_varvalue(data, "HOME", 4);
	}
	if (i - j > 0)
	{
		line = ft_substr(str, j, i - j);
		ft_lstadd_back(lst, ft_lstnew(line));
	}
	str = find_varvalue(data, "HOME", 4);
	if (line)
		ft_lstadd_back(lst, ft_lstnew(line));
	return (++i);
}

static	int	verify_expansion(t_minish *data, char *str, t_list **lst, int *j)
{
	int	i;
	int	quote;

	i = -1;
	quote = 1;
	while (str[++i])
	{
		if (are_quotes(str[i]) != quote && quote == 1)
			quote = are_quotes(str[i++]);
		if (str[i] == '$' && quote != 3)
			*j = expand_var(data, lst, str, i, *j);
		if (str[i] == '~' && quote == 1 && (i == 0 || str[i - 1] == ' ')
			&& (!str[i + 1] || str[i + 1] == ' ' || str[i + 1] == '/'))
			*j = expand_tilde(data, lst, str, i, *j);
		if (*j > i)
			i = *j - 1;
		if (quote == are_quotes(str[i]))
			quote = 1;
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
	// int		index;
	int		i;
	int		j;
	t_list	*lst;
	char	*subline;

	j = 0;
	// index = -1;
	lst = NULL;
	subline = NULL;
	while (data->tokens[++i])
	{
		i = verify_expansion(data, data->tokens[i], &lst, &j);
		if (!lst)
			return ;
		if (j < i)
		{
			subline = ft_substr(data->tokens[i], j, i - j);
			if (!subline)
				//error
			ft_lstadd_back(&lst, ft_lstnew(subline));
		}
		free(data->tokens[i]);
		data->tokens[i] = create_expanded_line(&lst);
	}
}
