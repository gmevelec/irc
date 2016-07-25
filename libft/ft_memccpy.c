/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:38:42 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/29 14:06:56 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char	*dst;
	char	*src;

	dst = (char *)s1;
	src = (char *)s2;
	while (n > 0)
	{
		*dst = *src;
		if (*src == c)
		{
			dst++;
			return (dst);
		}
		dst++;
		src++;
		n--;
	}
	return (NULL);
}
