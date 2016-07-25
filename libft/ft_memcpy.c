/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:54:15 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/29 14:08:11 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;

	i = 0;
	dest = s1;
	src = (char *)s2;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
