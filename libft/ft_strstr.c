/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 13:49:01 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/25 16:44:09 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	tmp_i;
	size_t	tmp_j;

	i = 0;
	if (ft_strlen(s2) == 0)
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		j = 0;
		tmp_i = i;
		tmp_j = j;
		while (s2[j] != '\0')
		{
			if (s1[tmp_i] == s2[tmp_j])
				tmp_j++;
			tmp_i++;
			if (tmp_j == ft_strlen(s2))
				return ((char *)&s1[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
