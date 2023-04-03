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
		return (ft_strdup(linepwd));
	linepwd = ft_strdup("/.");
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
	t_list	*prefix;
	char	*line1;
	char	*linepwd;
	size_t	len;

	linepwd = getpwd_forline(data);
	prefix = NULL;
	line1 = find_varvalue(data, "USER", 4);
	if (!line1)
		ft_lstadd_back(&prefix, ft_lstnew(ft_strdup("guest@minisHELL:")));
	else
		ft_lstadd_back(&prefix, ft_lstnew(ft_strjoin(line1, "@minisHELL:")));
	ft_lstadd_back(&prefix, ft_lstnew(linepwd));
	line1 = find_varvalue(data, "HOME", 4);
	if (line1)
		len = ft_strlen(line1);
	if (line1 && !ft_memcmp(ft_lstlast(prefix)->content, line1, len))
	{
		line1 = ft_strjoin("~", (char *)ft_lstlast(prefix)->content + len);
		free(ft_lstlast(prefix)->content);
		ft_lstlast(prefix)->content = line1;
	}
	ft_lstadd_back(&prefix, ft_lstnew(ft_strdup("$ ")));
	return (make_line_fromlst(&prefix));
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
