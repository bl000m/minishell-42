/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 13:11:06 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(int argc, char *argv[], t_minish *data)
{
	int		fd;

	if (argc != 6)
	{
		exit_clean(data);
		exit(1);
	}
	// write to pipe[1] instead
	fd = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		error_manager(6, data, NULL);
	getting_and_writing_input_on_file(argv[2], fd);
	data->file_in = open(".here_doc", O_RDONLY);
	if (data->file_in < 0)
		error_manager(6, data, NULL);
	switching_input_output(data, 's');
	close(data->file_in);
}

void	getting_and_writing_input_on_file(char *limiter, int fd)
{
	char	*input;

	while (1)
	{
		ft_printf("pipex here_doc> ");
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
