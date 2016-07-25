/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 10:37:41 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/05 10:48:02 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

void		nick(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	char	*tmp;

	if (check_nick(serveur, client, buf))
		return ;
	tmp = ft_strdup("\x1B[32m");
	tmp = ft_strjoin(tmp, client->name);
	client->name = ft_strdup(buf);
	tmp = ft_strjoin(tmp, " changed name for ");
	tmp = ft_strjoin(tmp, buf);
	tmp = ft_strjoin(tmp, ".\033[0m\n");
	serveur_to_all(serveur->clients, *client, actual, tmp);
	tmp = ft_strdup("\x1B[32mYou changed name for ");
	tmp = ft_strjoin(tmp, buf);
	tmp = ft_strjoin(tmp, ".\033[0m\n");
	write_client(client->sock, tmp);
}

void		msg(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	int		i;
	char	*msg;
	int		n;

	(void)actual;
	i = 0;
	while (buf[i] != ' ')
		i++;
	msg = get_msg(client->name, "\x1B[35mFrom ", buf + i + 1);
	buf[i] = 0;
	n = get_socket(serveur, client, buf);
	if (n == -1)
	{
		write_client(client->sock,
			"\x1B[31mThis person is not connected\033[0m\n");
		return ;
	}
	write_client(n, msg);
	msg = get_msg(buf, "\x1B[35mTo ", buf + i + 1);
	buf[i] = 0;
	write_client(client->sock, msg);
}

void		leave(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	char	*msg;

	(void)actual;
	if (client->channel)
	{
		if (!ft_strcmp(client->channel, buf))
		{
			msg = ft_strdup("\x1B[36mYou leaved channel: ");
			msg = ft_strjoin(msg, client->channel);
			msg = ft_strjoin(msg, ".\033[0m\n");
			serveur_to_chan(serveur, client, " has leaved the channel.");
			client->channel = NULL;
			write_client(client->sock, msg);
		}
		else
			write_client(client->sock,
				"\x1B[31mYou are not in this channel.\033[0m\n");
	}
}

void		join(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	char	*msg;

	(void)actual;
	if (check_channel(client, buf) == 1)
	{
		write_client(client->sock,
			"\x1B[31mYou are already in this channel.\033[0m\n");
		return ;
	}
	if (check_channel(client, buf) == -1)
	{
		write_client(client->sock, "\x1B[31mWrong channel name.\033[0m\n");
		return ;
	}
	if (client->channel)
		leave(serveur, client, client->channel, actual);
	msg = NULL;
	client->channel = ft_strdup(buf);
	msg = ft_strdup("\x1B[36mYou joined channel: ");
	msg = ft_strjoin(msg, buf);
	msg = ft_strjoin(msg, ".\033[0m\n");
	write_client(client->sock, msg);
	serveur_to_chan(serveur, client, " has joined the channel.");
}

void		who(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	int		i;
	char	*msg;

	(void)buf;
	(void)actual;
	i = 0;
	if (client->channel)
	{
		while (serveur->clients[i].name)
		{
			msg = ft_strdup(serveur->clients[i].name);
			msg = ft_strjoin(msg, "\n");
			if (!ft_strcmp(serveur->clients[i].channel, client->channel))
				write_client(client->sock, msg);
			i++;
		}
	}
	else
		write_client(client->sock, "\x1B[31mYou must join a channel.\033[0m\n");
}
