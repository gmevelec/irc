/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 11:38:38 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/28 18:10:10 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	i = (size_t)start;
	dst = (char *)malloc(sizeof(dst) * (len + 1));
	if (dst == NULL)
		return (NULL);
	while (j < len)
	{
		dst[j] = s[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
