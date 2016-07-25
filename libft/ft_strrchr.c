/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 16:03:10 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/25 17:13:10 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	s--;
	while (i > 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}
