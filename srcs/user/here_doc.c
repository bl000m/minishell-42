/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/07 14:17:33 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(t_minish *data, int *i, int fd)
{
	char	*input;
	char	*limiter;

	limiter = data->tokens[*i + 1];
	printf("limiter = %s\n", limiter);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return ;
		if (!input || (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
		{
			close(fd);
			break ;
		}
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
		input = NULL;
	}
	// free(input);
	// close(fd);
}
