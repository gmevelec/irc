/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:24:57 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/06 16:24:58 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

void			welcome(t_serveur serv, int n)
{
	write_client(serv.clients[n - 1].sock, "Welcome ");
	write_client(serv.clients[n - 1].sock, serv.clients[n - 1].name);
	write_client(serv.clients[n - 1].sock, " !\n");
}

char			*get_msg(char *name, char *str, char *buf)
{
	char	*msg;

	msg = ft_strdup(name);
	msg = ft_strjoin(msg, ": ");
	msg = ft_strjoin(msg, buf);
	msg = ft_strjoin(msg, "\033[0m\n");
	msg = ft_strjoin(str, msg);
	return (msg);
}

static void		invite_msg2(t_serveur *serveur, t_client *client, int sock)
{
	char	*msg;

	msg = ft_strdup("\x1B[36mYou invited ");
	msg = ft_strjoin(msg, serveur->clients[sock].name);
	msg = ft_strjoin(msg, " in channel.\033[0m\n");
	write_client(client->sock, msg);
	msg = ft_strdup("\x1B[36m");
	msg = ft_strjoin(msg, client->name);
	msg = ft_strjoin(msg, " invite you to join channel ");
	msg = ft_strjoin(msg, client->channel);
	msg = ft_strjoin(msg, " type \"/join ");
	msg = ft_strjoin(msg, client->channel);
	msg = ft_strjoin(msg, "\" to join.\033[0m\n");
	write_client(serveur->clients[sock].sock, msg);
}

void			invite_msg(t_serveur *serveur, t_client *client,
				char *buf, int sock)
{
	if (!client->channel)
	{
		write_client(client->sock,
			"\x1B[31mYou are not in a channel.\033[0m\n");
		return ;
	}
	if (sock == -1)
	{
		write_client(client->sock, "\x1B[31m");
		write_client(client->sock, buf);
		write_client(client->sock, " is not connected.\033[0m\n");
	}
	else if (sock == -2)
	{
		write_client(client->sock, "\x1B[31m");
		write_client(client->sock, buf);
		write_client(client->sock, " is already in chan.\033[0m\n");
	}
	else
		invite_msg2(serveur, client, sock);
}

void			list_msg(int sock, char **channels, int j)
{
	int		i;

	write_client(sock, "\x1B[33mList of channels: ");
	i = 0;
	while (i < j)
	{
		write_client(sock, "\n");
		write_client(sock, channels[i]);
		i++;
	}
	write_client(sock, "\033[0m\n");
}
