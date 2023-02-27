/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:36:33 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/27 12:56:33 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* remember to free (and = NULL) full_command*/
int	main(int argc, char *argv[], char *envp[])
{
	t_minish	*data;

	(void) argv;
	check_error(argc);
	data = init_data(envp);
	setting_prompt(data);
	// if (!(checking_here_doc(argc, argv, data)))
		// multiple_commands_handling(argc, argv, data);
	// communicating(data, argv, envp);
	return (0);
}

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

// void	multiple_commands_handling(int argc, char *argv[], t_minish *data)
// {
	// data->pos = 2;
	// data->n_cmd = argc - 3;
	// opening_files(data, argv, 's');
// 	switching_input_output(data, 's');
// 	close(data->file_in);
// }
