/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 15:11:53 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	checking_here_doc(int argc, char *argv[], t_minish *data)
// {
// 	if (argv[1] && (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		&& argv[1][8] == '\0')
// 	{
// 		data->pos = 3;
// 		data->n_cmd = 2;
// 		here_doc(argc, argv, data);
// 		opening_files(data, argv, 'h');
// 		return (1);
// 	}
// 	return (0);
// }

void	here_doc(t_minish *data, t_cmd **node, int *i)
{
	int		fd[2];

	// write to pipe[1] instead
    if (pipe(fd) == -1)
			error_manager(1, data, NULL);
	(*node)->output = fd[1];
    (*node)->next->input = fd[0];
	getting_and_writing_input_on_pipe(data->tokens[*i + 1], (*node)->output);
}

void	getting_and_writing_input_on_pipe(char *limiter, int fd)
{
	char	*input;

	while (1)
	{
		ft_printf("here_doc> ");
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
