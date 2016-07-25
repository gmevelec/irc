/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:49:45 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/30 20:38:47 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0 && ptr)
	{
		if (*ptr == (char)c)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
