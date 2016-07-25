/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 10:31:00 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/28 18:04:43 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		length;
	char				*dst;
	unsigned int		i;

	if (!s || !(*f))
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	dst = (char *)malloc(sizeof(dst) * (length + 1));
	if (dst == NULL)
		return (NULL);
	while (i < length)
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
