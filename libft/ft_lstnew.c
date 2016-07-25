/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 14:26:03 by gmevelec          #+#    #+#             */
/*   Updated: 2013/11/30 18:14:04 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*begin;

	begin = (t_list *)malloc(sizeof(t_list));
	if (content == NULL)
	{
		begin->content = NULL;
		begin->content_size = 0;
	}
	else
	{
		begin->content = (void *)malloc(sizeof(t_list) * content_size);
		ft_memcpy(begin->content, content, content_size);
		begin->content_size = content_size;
	}
	begin->next = NULL;
	return (begin);
}
