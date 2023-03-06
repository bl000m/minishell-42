/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/06 12:57:44 by mpagani          ###   ########.fr       */
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
		ft_printf("> ");
		input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			close(fd);
			exit(1);
		}
		if (input[ft_strlen(limiter)] == '\n' && limiter
			&& (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0))
		{
			close(fd);
			break ;
		}
		ft_putstr_fd(input, fd);
		free(input);
		input = NULL;
	}
	free(input);
	close(fd);
}
