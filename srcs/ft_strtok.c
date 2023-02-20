/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:09:35 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/20 17:55:50 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static char	*ft_dupstr(char const *s, int i, int j)
{
	char	*dup;
	int		x;

	dup = malloc(sizeof(char) * (j - i + 1));
	if (!dup)
		return (0);
	x = 0;
	while (s[i] && i < j)
	{
		dup[x] = s[i];
		x++;
		i++;
	}
	dup[x] = 0;
	return (dup);
}

static char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

int	are_quotes(char c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (3);
	return (1);
}

static int	checking_del(char c, char *delimiters)
{
	int	j;

	j = 0;
	while (delimiters[j])
	{
		if (delimiters[j] == c)
			return (are_quotes(delimiters[j]));
		j++;
	}
	return (0);
}

// recheck scenario ' ' are not after and before spaces
static int	ft_words(char const *s, char *delimiters)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	j = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && checking_del(s[i], delimiters) && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] == '\"')
		{
			j = i;
			while (s[j + 1] && s[j + 1] != '\"')
				j++;
			words++;
			i = j + 1;
		}
		else
		{
			if (!checking_del(s[i], delimiters) && s[i] != 0)
			{
				words++;
				i++;
			}
			while (s[i] && !checking_del(s[i], delimiters))
				i++;
		}
		i++;
	}
	return (words);
}

static	char	**ft_fill_lines(char const *s, char *delimiters, char **strs)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] && checking_del(s[i], delimiters) && s[i] != '\"' && s[i] != '\'')
			i++;
		if (s[i] == '\"')
		{
			j = i;
			while (s[j + 1] && s[j + 1] != '\"')
				j++;
			strs[x] = ft_dupstr(s, i, j + 2);
			if (strs[x] == 0)
				return (ft_free(strs));
			x++;
			i = j + 1;
		}
		else if (s[i] == '\'')
		{
			j = i;
			while (s[j + 1] && s[j + 1] != '\'')
				j++;
			strs[x] = ft_dupstr(s, i, j + 2);
			if (strs[x] == 0)
				return (ft_free(strs));
			x++;
			i = j + 1;
		}
		else
		{
			while (s[i] && checking_del(s[i], delimiters))
				i++;
			j = i;
			while (s[j] && !checking_del(s[j], delimiters))
				j++;
			if (checking_del(s[j], delimiters) || (!s[j] && !checking_del(s[j - 1], delimiters)))
			{
				strs[x] = ft_dupstr(s, i, j);
				if (strs[x] == 0)
					return (ft_free(strs));
				x++;
				i = j;
			}
		}
		i++;
	}
	return (strs);
}

// to be recheck the n_tokens
char	**ft_strtok(char *s, char *delimiters)
{
	char	**strs;
    int     n_tokens;

	if (!s)
		return (0);
    n_tokens = ft_words(s, delimiters);
	ft_printf("tokens = %d\n", n_tokens);
	strs = malloc(sizeof(char *) * (n_tokens + 1));
	if (!strs)
		return (NULL);
	strs = ft_fill_lines(s, delimiters, strs);
	if (strs)
		strs[n_tokens] = 0;
	return (strs);
}
