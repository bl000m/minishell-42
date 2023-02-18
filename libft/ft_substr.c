/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:03:40 by mpagani           #+#    #+#             */
/*   Updated: 2022/11/15 11:12:05 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	new_str = malloc(sizeof(*new_str) * len + 1);
	if (!new_str)
		return (NULL);
	while (i < len && s[i] && (size_t)start <= ft_strlen(s))
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}
