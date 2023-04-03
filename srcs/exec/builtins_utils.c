/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:17:56 by FelipeBelfo       #+#    #+#             */
/*   Updated: 2023/04/01 15:10:34 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_validvarname(char *varname, size_t len)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(varname[i]) && varname[i] != '_')
		return (0);
	while (varname[++i] && i < len)
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (0);
	return (1);
}

char	*getpwd_forline(t_minish *data)
{
	char	*linepwd;

	linepwd = find_varvalue(data, "PWD", 3);
	if (linepwd)
		return (mini_strdup(data, linepwd));
	linepwd = mini_strdup(data, "/.");
	return (linepwd);
}

/**
 * @brief
 * Gets the actuel path to create a string to put on the prefix of the executable
 * It will create the pattern
 * "LOGIN@@minishell:PATH$ "
 * (if that's the case will replace the HOME path by '~')
 * to be used in the readline()
*/
char	*get_lineprefix(t_minish *data)
{
	t_list	*res;
	char	*s1;
	char	*linepwd;
	size_t	len;

	linepwd = getpwd_forline(data);
	res = NULL;
	s1 = find_varvalue(data, "USER", 4);
	if (!s1)
		ft_lstadd_back(&res, ft_lstnew(mini_strdup(data, "guest@minisHELL:")));
	else
		ft_lstadd_back(&res, ft_lstnew(mini_join(data, s1, "@minisHELL:")));
	ft_lstadd_back(&res, ft_lstnew(linepwd));
	s1 = find_varvalue(data, "HOME", 4);
	if (s1)
		len = ft_strlen(s1);
	if (s1 && !ft_memcmp(ft_lstlast(res)->content, s1, len))
	{
		s1 = mini_join(data, "~", (char *)ft_lstlast(res)->content + len);
		free(ft_lstlast(res)->content);
		ft_lstlast(res)->content = s1;
	}
	ft_lstadd_back(&res, ft_lstnew(mini_strdup(data, "$ ")));
	return (make_line_fromlst(data, &res));
}

void	executing_builtin(t_minish *data, t_cmd **cmd)
{
	if (!ft_strncmp((*cmd)->full_cmd[0], "pwd", 3))
		mini_pwd(data);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "env", 3))
		mini_env(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "unset", 5))
		mini_unset(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "echo", 4))
		mini_echo(*cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "export", 6))
		mini_export(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "cd", 2))
		mini_cd(data, *cmd);
	else if (!ft_strncmp((*cmd)->full_cmd[0], "exit", 4))
		mini_exit(data, cmd);
}
