/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/03 17:29:14 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* builtin to be exec in parent process: */

void	mini_unset(t_minish *data, t_cmd *cmd)
{
	t_dict	*curr;
	size_t	len;
	int		i;
	char	*variable;

	i = 0;
	g_status = EXIT_SUCCESS;
	while (cmd->full_cmd[++i])
	{
		variable = cmd->full_cmd[i];
		len = ft_strlen(variable);
		if (!is_validvarname(variable, len) && ft_memcmp(variable, "_", len))
		{
			error_manager(0, EC_UNSET, variable, EXIT_FAILURE);
			continue ;
		}
		if (!ft_memcmp(variable, "_", len))
			continue ;
		curr = dict_findvar(data->envp, variable, len);
		if (curr && ft_memcmp(curr->key, "SHLVL", curr->key_len))
			dict_delone(&data->envp, curr);
		else if (!ft_memcmp(curr->key, "SHLVL", curr->key_len))
			if (!set_varvalue(data->envp, curr->key, curr->key_len, "0"))
				hard_exit(data, NULL, NULL);
	}
}

void	mini_cd(t_minish *data, t_cmd *cmd)
{
	char	*pwd;

	if (!cmd->full_cmd[1])
		return ;
	if (cmd->full_cmd[2])
		error_manager(0, EC_CDARG, NULL, EXIT_FAILURE);
	else
	{
		if (chdir(cmd->full_cmd[1]) != 0)
		{
			error_manager(0, EC_CDNODIR, NULL, EXIT_FAILURE);
			return ;
		}
		pwd = getcwd(NULL, 0);
		if (!pwd || !set_varvalue(data->envp, "OLDPWD", 6, pwd))
			hard_exit(data, NULL, NULL);
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd || !set_varvalue(data->envp, "PWD", 3, pwd))
			hard_exit(data, NULL, NULL);
		free(pwd);
		g_status = EXIT_SUCCESS;
	}
}

void	mini_exit(t_minish *data, t_cmd **cmd)
{
	int	i;

	i = -1;
	printf("exit\n");
	if (!(*cmd)->full_cmd[1])
	{
		exit_clean(data);
		exit(0);
	}
	if ((*cmd)->full_cmd[2])
		printf("exit: too many arguments\n");
	else
	{
		while ((*cmd)->full_cmd[1][++i])
		{
			if ((*cmd)->full_cmd[1][i] < '0' || (*cmd)->full_cmd[1][i] > '9')
				error_manager(0, EC_EXIT, (*cmd)->full_cmd[1], 2);
			else if (ft_isdigit((*cmd)->full_cmd[1][i]))
				g_status = (ft_atoi((*cmd)->full_cmd[1])) % 256;
			exit_clean(data);
			exit(g_status);
		}
	}
}
