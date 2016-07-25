/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:55:12 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/06 16:55:13 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.h"
#include "../../libft/libft.h"

void		read_msg(char *buf)
{
	char	*p;

	read(0, buf, BUF_SIZE);
	if ((p = ft_strstr(buf, "\n")) != NULL)
		*p = 0;
	else
		buf[BUF_SIZE] = 0;
}

int			read_serveur(int sock, char *buf)
{
	int		n;

	n = 0;
	if ((n = recv(sock, buf, BUF_SIZE, 0)) < 0)
		exit_error("Recv");
	buf[n] = 0;
	return (n);
}

void		write_server(int sock, char *buf)
{
	if (send(sock, buf, ft_strlen((char *)buf), 0) < 0)
		exit_error("Send");
}
