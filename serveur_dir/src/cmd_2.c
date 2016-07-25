/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 10:50:52 by gmevelec          #+#    #+#             */
/*   Updated: 2015/05/07 10:50:52 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/serveur.h"
#include "../../libft/libft.h"

void		help(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	int		i;

	i = 0;
	(void)serveur;
	(void)buf;
	(void)actual;
	write_client(client->sock, "\x1B[33mCommands available:\n");
	while (g_ptr[i].cmd)
	{
		write_client(client->sock, g_ptr[i].cmd);
		write_client(client->sock, "\n");
		i++;
	}
	write_client(client->sock, "/connect\n");
	write_client(client->sock, "/quit");
	write_client(client->sock, "\033[0m\n");
}

void		invite(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	int		i;
	int		sock;

	sock = -1;
	i = 0;
	while (i < actual)
	{
		if (serveur->clients[i].name && client->channel)
		{
			if (!ft_strcmp(serveur->clients[i].name, buf) &&
				ft_strcmp(serveur->clients[i].channel,
					client->channel))
				sock = i;
			else if (!ft_strcmp(serveur->clients[i].name, buf) &&
				!ft_strcmp(serveur->clients[i].channel,
					client->channel))
				sock = -2;
		}
		i++;
	}
	invite_msg(serveur, client, buf, sock);
}

void		me(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = ft_strdup("\x1B[35m");
	tmp = ft_strjoin(tmp, client->name);
	tmp = ft_strjoin(tmp, " ");
	tmp = ft_strjoin(tmp, buf);
	tmp = ft_strjoin(tmp, "\033[0m\n");
	while (i < actual)
	{
		if (!ft_strcmp(client->channel, serveur->clients[i].channel))
			write_client(serveur->clients[i].sock, tmp);
		i++;
	}
}

void		list(t_serveur *serveur, t_client *client, char *buf, int actual)
{
	char	**channels;
	int		i;
	int		j;

	(void)buf;
	channels = malloc(actual * sizeof(char *));
	j = 0;
	i = 0;
	while (i < actual)
	{
		if (serveur->clients[i].channel &&
			is_not_in(channels, serveur->clients[i].channel))
		{
			channels[j] = ft_strdup(serveur->clients[i].channel);
			j++;
		}
		i++;
	}
	if (!channels[0])
		write_client(client->sock, "\x1B[31mNo channels open. \
Use \"/join #chan\" to create and join a channel.\033[0m\n");
	else
		list_msg(client->sock, channels, j);
}

void		quit(t_serveur *serveur, t_client *client, char *buf, int *actual)
{
	int		i;

	(void)buf;
	i = 0;
	while (ft_strcmp(serveur->clients[i].name, client->name))
		i++;
	disconnect_client(serveur, actual, i);
}
