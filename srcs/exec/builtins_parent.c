/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/23 15:30:46 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* builtin to be exec in parent process: */
void	unset(t_minish *data, t_cmd *cmd)
{
	t_dict	*curr;
	size_t	len;
	int		i;
	char	*variable;

	i = 0;
	while (cmd->full_cmd[++i])
	{
		variable = cmd->full_cmd[i];
		len = ft_strlen(variable);
		if (!ft_memcmp(variable, "_", len))
			continue ;
		curr = dict_findvar(data->envp, variable, len);
		if (curr)
			dict_delone(&data->envp, curr);
	}
	g_status = EXIT_SUCCESS;
}

void	export(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;
	size_t	len;
	char	*arg;
	int		i;

	if (!cmd->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (cmd->full_cmd[++i])
	{
		arg = cmd->full_cmd[i];
		len = 0;
		while (arg[len] && arg[len] != '=')
			len++;
		if (ft_memcmp(arg, "_", len))
		{
			ptr = dict_findvar(data->envp, arg, len);
			if (!ptr)
				dict_addback(&data->envp, dict_newnode(arg));
			if (arg[len] == '=' && ptr)
				set_varvalue(data->envp, ptr->key, ptr->key_len, &arg[len + 1]);
		}
	}
	g_status = EXIT_SUCCESS;
}

void	cd(t_minish *data, t_cmd *cmd)
{
	char	*pwd;

	if (!cmd->full_cmd[1])
		return ;
	if (cmd->full_cmd[2])
		error_manager(14, data, &cmd);
	else
	{
		if (chdir(cmd->full_cmd[1]) != 0)
		{
			error_manager(13, data, &cmd);
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

void	mini_exit(t_cmd **cmd)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (!(*cmd)->full_cmd[1])
		exit(0);
	if ((*cmd)->full_cmd[2])
		printf("exit: too many arguments\n");
	else
	{
		while ((*cmd)->full_cmd[1][i])
		{
			if ((*cmd)->full_cmd[1][i] < '0' || (*cmd)->full_cmd[1][i] > '9')
			{
				printf("exit: %s: numeric argument required\n",
					(*cmd)->full_cmd[1]);
				exit(2);
			}
			else if ((*cmd)->full_cmd[1][i] > '0'
				&& (*cmd)->full_cmd[1][i] < '9')
				exit((ft_atoi((*cmd)->full_cmd[1])) % 256);
			i++;
		}
	}
}
