/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:40:13 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/04 10:56:46 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_write(t_minish *data, int ignore_exp, char *input)
{
	char	*expanded_input;
	t_list	*tmp;

	tmp = data->aux;
	data->aux = NULL;
	if (ignore_exp)
		ft_lstadd_back(&tmp, ft_lstnew(input));
	else
	{
		expanded_input = heredoc_expand(data, input);
		if (expanded_input)
			ft_lstadd_back(&tmp, ft_lstnew(expanded_input));
		else
			ft_lstadd_back(&tmp, ft_lstnew(input));
	}
	ft_lstadd_back(&tmp, ft_lstnew(mini_strdup(data, "\n")));
	input = NULL;
	data->aux = tmp;
}

void	child_heredoc(t_minish *data, char *lim, int fd, int ignore_exp)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strncmp(input, lim, ft_strlen(lim) + 1) == 0))
		{
			if (!input)
				error_manager(0, EC_HEREDOC, lim, 131);
			break ;
		}
		heredoc_write(data, ignore_exp, input);
	}
	if (input)
		free(input);
	input = make_line_fromlst(data, &data->aux);
	write(fd, input, ft_strlen(input));
	free(input);
	close(fd);
	exit(g_status);
}

void	here_doc(t_minish *data, int *i, int fd, t_cmd **node)
{
	char	*lim;
	pid_t	here_doc_pid;
	int		fd_int;
	int		ignore_exp;
	int		process_status;

	set_signals(HEREDOC);
	fd_int = dup(STDIN_FILENO);
	lim = getting_rid_of_quotes(data, data->tokens[*i + 1]);
	ignore_exp = ft_strlen(data->tokens[*i + 1]) - ft_strlen(lim);
	g_status = 0;
	here_doc_pid = fork();
	if (here_doc_pid == 0)
		child_heredoc(data, lim, fd, ignore_exp);
	close(fd);
	waitpid(here_doc_pid, &process_status, 0);
	g_status = WEXITSTATUS(process_status);
	free(lim);
	if ((*node)->file_in)
		(*node)->file_in = 0;
	dup2(fd_int, STDIN_FILENO);
}

int	heredoc_expand_aux(t_minish *data, char *line, int i, int j)
{
	int		k;
	char	*tmp;

	if (i - j > 0)
		ft_lstadd_back(&data->aux, ft_lstnew(ft_substr(line, j, i - j)));
	k = 2;
	if (ft_isalpha(line[i + 1]) || line[i + 1] == '_')
		while (ft_isalnum(line[i + k]) || line[i + k] == '_')
			k++;
	if (line[i + 1] == '?')
		line = ft_itoa(g_status);
	else
	{
		tmp = find_varvalue(data, line + i + 1, k - 1);
		line = mini_strdup(data, tmp);
	}
	if (!line)
		line = ft_calloc(1, sizeof(char));
	ft_lstadd_back(&data->aux, ft_lstnew(line));
	return (i + k);
}

/**
 * @brief
 * Expands all the variables, whitout handling the quotes.
 * To be used by heredoc.
*/
char	*heredoc_expand(t_minish *data, char *line)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			j = heredoc_expand_aux(data, line, i, j);
			i = j - 1;
		}
	}
	if (data->aux)
	{
		ft_lstadd_back(&data->aux, ft_lstnew(ft_substr(line, j, i - j)));
		return (make_line_fromlst(data, &data->aux));
	}
	return (NULL);
}
