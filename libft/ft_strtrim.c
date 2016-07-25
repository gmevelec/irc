/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 13:26:19 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/28 18:07:06 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		c;
	char	*dst;
	int		i;

	c = 0;
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	i = ft_strlen(s);
	while ((s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n') && i > 0)
		i--;
	dst = (char *)malloc(sizeof(dst) * i);
	if (dst == NULL)
		return (NULL);
	while (c < i)
	{
		dst[c] = s[c];
		c++;
	}
	dst[c] = '\0';
	return (dst);
}
