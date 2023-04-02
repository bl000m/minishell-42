/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/04/01 15:09:56 by mpagani          ###   ########.fr       */
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
			set_varvalue(data->envp, curr->key, curr->key_len, "0");
	}
}

void	mini_export(t_minish *data, t_cmd *cmd)
{
	int	i;

	g_status = EXIT_SUCCESS;
	if (!cmd->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (cmd->full_cmd[++i])
		export_aux(data, cmd->full_cmd[i]);
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
		set_varvalue(data->envp, "OLDPWD", 6, pwd);
		free(pwd);
		pwd = getcwd(NULL, 0);
		set_varvalue(data->envp, "PWD", 3, pwd);
		free(pwd);
		g_status = EXIT_SUCCESS;
	}
}

// add exit_clean
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
