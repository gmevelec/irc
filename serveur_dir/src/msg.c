/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:30:55 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 10:54:12 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

void		write_client(int sock, char *buf)
{
	send(sock, buf, ft_strlen(buf), 0);
}

void		serveur_to_chan(t_serveur *serveur, t_client *client, char *buf)
{
	char	*msg;
	int		i;

	msg = ft_strdup("\x1B[36m");
	msg = ft_strjoin(msg, client->name);
	msg = ft_strjoin(msg, buf);
	msg = ft_strjoin(msg, "\033[0m\n");
	i = 0;
	while (serveur->clients[i].name)
	{
		if (!ft_strcmp(serveur->clients[i].channel, client->channel))
			write_client(serveur->clients[i].sock, msg);
		i++;
	}
}

void		serveur_to_all(t_client *dest, t_client writer,
					int actual, char *buf)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		if (writer.sock != dest[i].sock)
			write_client(dest[i].sock, buf);
		i++;
	}
}

void		client_to_all(t_client *dest, t_client writer,
					int actual, char *buf)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(writer.name);
	tmp = ft_strjoin(tmp, ": ");
	tmp = ft_strjoin(tmp, buf);
	tmp = ft_strjoin(tmp, "\n");
	while (i < actual)
	{
		if (writer.sock != dest[i].sock &&
			!ft_strcmp(dest[i].channel, writer.channel))
			write_client(dest[i].sock, tmp);
		i++;
	}
}

int			read_client(int sock, char *buf)
{
	int		n;

	n = 0;
	n = recv(sock, buf, BUF_SIZE, 0);
	buf[n] = 0;
	return (n);
}
