/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:57:45 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/30 20:36:15 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*a;
	char	*b;

	a = dest;
	b = (char *)src;
	if (a <= b || b >= (a + n))
	{
		while (n--)
			*a++ = *b++;
	}
	else
	{
		a = a + n - 1;
		b = b + n - 1;
		while (n--)
			*a-- = *b--;
	}
	return (dest);
}
