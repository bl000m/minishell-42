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

/* builtin to be exec in parent process: */

void	unset(t_minish *data, t_cmd *cmd)
{
	t_dict	*curr;
	size_t	exit_code;
	size_t	len;
	int		i;
	char	*variable;

	i = 0;
	exit_code = EXIT_SUCCESS;
	while (cmd->full_cmd[++i])
	{
		variable = cmd->full_cmd[i];
		len = ft_strlen(variable);
		if (!is_validvarname(variable, len) && ft_memcmp(variable, "_", len))
		{
			exit_code = EXIT_FAILURE;
			printf("minishell: unset: `%s': not a valid identifier \n", variable);
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
	g_status = exit_code;
}

void	export(t_minish *data, t_cmd *cmd)
{
	t_dict	*ptr;
	size_t	len;
	char	*arg;
	int		i;

	g_status = EXIT_SUCCESS;
	if (!cmd->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (cmd->full_cmd[++i])
	{
		arg = cmd->full_cmd[i];
		len = 0;
		while (arg[len] && arg[len] != '=')
			len++;
		if (is_validvarname(arg, len) && ft_memcmp(arg, "_", len))
		{
			ptr = dict_findvar(data->envp, arg, len);
			if (!ptr)
				dict_addback(&data->envp, dict_newnode(arg));
			if (arg[len] == '=' && ptr)
				set_varvalue(data->envp, ptr->key, ptr->key_len, &arg[len + 1]);
		}
		else if (ft_memcmp(arg, "_", len))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			g_status = EXIT_FAILURE;
		}
	}
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
