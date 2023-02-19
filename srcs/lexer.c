/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:31:27 by fbelfort          #+#    #+#             */
/*   Updated: 2023/02/19 17:48:14 by fbelfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief
 * It takes a string and compares with the list of the 
 * environment variables. If the variable is found it will return the value 
 * of the variable. Otherwise it will return NULL.
 * 
 *  
*/
char	*find_varvalue(char *var)
{
	int	i;
    int size;

	i = 0;
    size = ft_strlen(var);
	while (data->envp[i] && ft_strncmp(data->envp[i], var, size))
		i++;
	if (data->envp[i] != NULL)
		return (data->envp[i] + size + 1);
	else
		return (NULL);
}

static char    *create_expanded_line(t_list **lst)
{
    char    *line;
    t_list  *tmp;
    size_t  i;
    size_t  size;

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
    while (*lst)
    {
        i = ft_strlen((*lst)->content);
        ft_memcpy(&line[size], (*lst)->content, i);
        size += i;
    }
    ft_lstclear(lst, free);
    return (line);
}

static int expand_var(t_list **lst, char *str, int i, int j)
{
    int     k;
    char    *line;
    char    *line_tmp;

    if (i - j > 0)
    {
        line = ft_substr(str, j, i - j);
        ft_lstadd_back(lst, ft_lstnew(line));
    }
    k = 1;
    while (str[i + k] != '"' && str[i + k] != ' ' && str[i + k] != "'")
        k++;
    line_tmp = ft_substr(str, i + 1, k);
    line = find_varvalue(line_tmp);
    free(line_tmp);
    ft_lstadd_back(lst, ft_lstnew(line));
    return (i + k);
}

static void    try_to_expand(char *str)
{
    int quote;
    int i;
    int j;
    t_list  *tmp;

    quote = 1;
    i = -1;
    j = 0;
    tmp = NULL;
    while (str[++i])
    {
        if (are_quotes(str[i]) != quote && quote == 1)
            quote = are_quotes(str[i++]);
        if (str[i] == '$' && quote != 3)
            j = expand_var(&tmp, str, i, j);
        if (j > i)
            i = j - 1;
        if (quote == are_quotes(str[i]))
            quote = 1;
    }
    if (!tmp)
        return ;
    if (j < i)
        ft_lstadd_back(&tmp, ft_lstnew(ft_substr(str, j, i - j)));
    free(str);
    str = create_expanded_line(&tmp);
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
void    expand_path(t_minish data)
{
    int i;

    i = -1;
    while (data->tokens[++i])
    {
        if (!ft_strncmp(data->tokens[i], "~", 2))
        {
            free(str);
            str = find_varvalue("HOME"); // --> to verify beacuse I'm not sure from where the bash takes it
            return ;
        }
        else
            try_to_expand(data->tokens[i]);
    }
    
}