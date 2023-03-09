/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:19:17 by fbelfort          #+#    #+#             */
/*   Updated: 2023/03/09 15:25:54 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* check if we need to return a g_status*/
void	unset(t_minish *data)
{
	t_dict	*curr;
	t_dict	*next;
	size_t	len;
	int		i;
	char	*variable;

	i = 0;
	while (data->cmds->full_cmd[++i])
	{
		variable = data->cmds->full_cmd[i];
		len = ft_strlen(variable);
		if (len == 1 && !ft_memcmp(variable, "_", 1))
			return ;
		curr = dict_findvar(data->envp, variable, len);
		printf("curr = %s\n", curr->key);
		if (curr)
		{
			printf("HERE?\n");
			next = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			curr = next;
		}

		printf("variable: %s\n", variable);
	}
	curr = data->envp;
	while (curr)
	{
		printf("%s\n", curr->key);
		curr = curr->next;
	}
}

void	env(t_minish *data)
{
	t_dict	*ptr;

	if (data->cmds->full_cmd[1])
	{
		printf("Error: We have to manage the errors\n");
		exit(EXIT_FAILURE);
	}
	ptr = data->envp;
	while (ptr)
	{
		if (ptr->has_value)
			printf("%s=%s\n", ptr->key, ptr->value);
		ptr = ptr->next;
	}
	exit(0);
}

void	export(t_minish *data)
{
	t_dict	*ptr;
	size_t	len;
	char	*arg;
	int		i;

	if (!data->cmds->full_cmd[1])
		print_sorted(data->envp);
	i = 0;
	while (data->cmds->full_cmd[++i])
	{
		arg = data->cmds->full_cmd[i];
		len = 0;
		while (arg[len] && arg[len] != '=')
			len++;
		ptr = dict_findvar(data->envp, arg, len);
		if (!ptr)
			dict_addback(&data->envp, dict_newnode(arg));
		if (arg[len] == '=' && ptr)
			set_varvalue(data->envp, ptr->key, ptr->key_len, &arg[len + 1]);
	}
}

void	echo(t_minish *data)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (data->cmds->full_cmd[++i])
	{
		if (data->cmds->full_cmd[i][0] == '-'
			&& data->cmds->full_cmd[i][1] == 'n')
		{
			j = 2;
			while (data->cmds->full_cmd[i][j] == 'n')
				j++;
			if (!data->cmds->full_cmd[i][j] && n == i - 1)
				n = i;
		}
		if (n != i)
			printf("%s", data->cmds->full_cmd[i]);
		if (data->cmds->full_cmd[i + 1] && n != i)
			printf(" ");
	}
	if (!n)
		printf("\n");
	exit (0);
}
