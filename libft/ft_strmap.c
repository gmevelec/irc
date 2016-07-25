/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 19:58:10 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/30 20:41:25 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		length;
	char	*dst;
	int		i;

	if (!s || !(*f))
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	dst = (char *)malloc(sizeof(dst) * (length + 1));
	while (i < length)
	{
		dst[i] = (*f)(s[i]);
		i++;
	}
	return (dst);
}
